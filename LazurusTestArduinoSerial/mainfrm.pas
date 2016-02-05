unit Mainfrm;

{$mode objfpc}{$H+}
//------------------------------------------------------------------------------
interface

uses
  Classes,
  SysUtils,
  FileUtil,
  Forms,
  Controls,
  Graphics,
  Dialogs,
  synaser,
  StdCtrls,
  ExtCtrls,
  ComCtrls;

type

  { TfrmMain }

  TfrmMain = class(TForm)
    btnConnect: TButton;
    btnClose: TButton;
    btnDisconnect: TButton;
    btnRefresh: TButton;
    cmbCommDataBits: TComboBox;
    cmbCommParity: TComboBox;
    cmbCommPorts: TComboBox;
    cmbCommSpeed: TComboBox;
    cmbCommStopBits: TComboBox;
    Label1: TLabel;
    lblSelectDataBits: TLabel;
    lblSelectParity: TLabel;
    lblSelectSpeed: TLabel;
    lblSelectStopBits: TLabel;
    Panel1: TPanel;
    pnlConnect: TPanel;
    Shape1: TShape;
    Shape2: TShape;
    Shape3: TShape;
    trkRed: TTrackBar;
    trkGreen: TTrackBar;
    trkBlue: TTrackBar;
    procedure btnCloseClick(Sender: TObject);
    procedure btnConnectClick(Sender: TObject);
    procedure btnRefreshClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure trkGreenChange(Sender: TObject);
  private
    fBlockSerial : TBlockSerial;
  protected
    Function Connect() : boolean;

    procedure FillCommPortCombo();
    procedure FillCommSpeedCombo();
    procedure FillCommDataBitsCombo();
    procedure FillCommParityCombo();
    procedure FillCommStopBitsCombo();

    procedure Refresh();

    procedure SetControls(aConnect : boolean);
  public
    property BlockSerial : TBlockSerial read fBlockSerial write fBlockSerial;
  end;

var
  frmMain: TfrmMain;

//------------------------------------------------------------------------------
implementation
{$R *.lfm}

uses
  Registry;

{ TfrmMain }
//------------------------------------------------------------------------------
procedure TfrmMain.btnConnectClick(Sender: TObject);
begin
  if Connect() then
    SetControls(true);
end;

//------------------------------------------------------------------------------
procedure TfrmMain.btnCloseClick(Sender: TObject);
begin
  Close();
end;

//------------------------------------------------------------------------------
procedure TfrmMain.btnRefreshClick(Sender: TObject);
begin
  Refresh();
end;

//------------------------------------------------------------------------------
procedure TfrmMain.FormCreate(Sender: TObject);
begin
  fBlockSerial := TBlockSerial.Create;

  SetControls(false);
  Refresh();
end;

//------------------------------------------------------------------------------
procedure TfrmMain.FormDestroy(Sender: TObject);
begin
  FreeAndNil(fBlockSerial);
end;

//------------------------------------------------------------------------------
procedure TfrmMain.trkGreenChange(Sender: TObject);
begin
  BlockSerial.SendString('S');
  BlockSerial.SendByte(trkRed.Position);
  BlockSerial.SendByte(trkGreen.Position);
  BlockSerial.SendByte(trkBlue.Position);
  BlockSerial.SendString(#10);
end;

//------------------------------------------------------------------------------
function TfrmMain.Connect(): boolean;
var
  Parity : ansistring;
  RecStr : ansistring;
begin
  Result := false;
  Parity := cmbCommParity.Items[cmbCommParity.ItemIndex];

  BlockSerial.Config(strtoint(cmbCommSpeed.Items[cmbCommSpeed.ItemIndex]),
                     strtoint(cmbCommDataBits.Items[cmbCommDataBits.ItemIndex]),
                     Parity[1],
                     strtoint(cmbCommStopBits.Items[cmbCommStopBits.ItemIndex]),
                     false,
                     true);
  BlockSerial.Connect(cmbCommPorts.Items[cmbCommPorts.ItemIndex]);
  Sleep(3000);
  BlockSerial.Connect(cmbCommPorts.Items[cmbCommPorts.ItemIndex]);


  BlockSerial.SendString('P' + #10);
  RecStr := BlockSerial.Recvstring(5000);
  if RecStr = 'D' then
    Result := true;
end;

//------------------------------------------------------------------------------
procedure TfrmMain.FillCommPortCombo();
var
  Reg : TRegistry;
  ValueNames : TStringList;
  NameIndex : integer;
  ValueName : string;
begin
  cmbCommPorts.Clear();
  Reg := TRegistry.Create();
  try
    ValueNames := TStringList.Create;
    try

      Reg.RootKey := HKEY_LOCAL_MACHINE;
      if Reg.OpenKeyReadOnly('HARDWARE\DEVICEMAP\SERIALCOMM') then
      begin
        Reg.GetValueNames(ValueNames);

        for NameIndex := 0 to ValueNames.Count-1 do
        begin
          ValueName := Reg.ReadString(ValueNames[NameIndex]);
          cmbCommPorts.AddItem(ValueName, nil);
        end;
      end;

      if cmbCommPorts.Items.Count > 0 then
        cmbCommPorts.ItemIndex := 0;

    finally
      FreeAndNil(ValueNames);
    end;
  finally
    FreeAndNil(Reg);
  end;
end;

//------------------------------------------------------------------------------
procedure TfrmMain.FillCommSpeedCombo();
begin
  cmbCommSpeed.Clear();
  cmbCommSpeed.AddItem('1200',nil);
  cmbCommSpeed.AddItem('2400',nil);
  cmbCommSpeed.AddItem('4800',nil);
  cmbCommSpeed.AddItem('9600',nil);
  cmbCommSpeed.AddItem('19200',nil);
  cmbCommSpeed.AddItem('38400',nil);
  cmbCommSpeed.AddItem('57600',nil);
  cmbCommSpeed.AddItem('115200',nil);

  cmbCommSpeed.ItemIndex := 6;
end;

//------------------------------------------------------------------------------
procedure TfrmMain.FillCommDataBitsCombo;
begin
  cmbCommDataBits.Clear();
  cmbCommDataBits.AddItem('8',nil);
  cmbCommDataBits.AddItem('7',nil);

  cmbCommDataBits.ItemIndex := 0;
end;

//------------------------------------------------------------------------------
procedure TfrmMain.FillCommParityCombo;
begin
  //N - None, O - Odd, E - Even, M - Mark or S - Space
  cmbCommParity.Clear();
  cmbCommParity.AddItem('N',nil);
  cmbCommParity.AddItem('E',nil);
  cmbCommParity.AddItem('O',nil);
  cmbCommParity.AddItem('M',nil);
  cmbCommParity.AddItem('S',nil);

  cmbCommParity.ItemIndex := 0;
end;

//------------------------------------------------------------------------------
procedure TfrmMain.FillCommStopBitsCombo;
begin
  cmbCommStopBits.Clear();
  cmbCommStopBits.AddItem('1',nil);
  cmbCommStopBits.AddItem('2',nil);

  cmbCommStopBits.ItemIndex := 0;
end;

//------------------------------------------------------------------------------
procedure TfrmMain.Refresh();
begin
  FillCommPortCombo();
  FillCommSpeedCombo();
  FillCommDataBitsCombo();
  FillCommParityCombo();
  FillCommStopBitsCombo();
end;

//------------------------------------------------------------------------------
procedure TfrmMain.SetControls(aConnect: boolean);
begin
  cmbCommPorts.Enabled := not aConnect;
  cmbCommSpeed.Enabled := not aConnect;
  cmbCommDataBits.Enabled := not aConnect;
  cmbCommParity.Enabled := not aConnect;
  cmbCommStopBits.Enabled := not aConnect;

  btnRefresh.Enabled := not aConnect;
  btnConnect.Enabled := not aConnect;

  btnDisconnect.Enabled := aConnect;
  trkRed.Enabled   := aConnect;
  trkGreen.Enabled := aConnect;
  trkBlue.Enabled  := aConnect;
end;


end.

