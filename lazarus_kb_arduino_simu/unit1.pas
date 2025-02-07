unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, ExtCtrls, StdCtrls,
  Menus, IdTCPServer, IdCustomTCPServer, IdContext,
  IdGlobal, Math, DateUtils;

const poly=$A001;
      init=$FFFF;


const nbekey=64;

type

  { TForm1 }

  TForm1 = class(TForm)
    ButtonPrendreK1: TButton;
    ButtonPrendreK10: TButton;
    ButtonPrendreK11: TButton;
    ButtonPrendreK12: TButton;
    ButtonPrendreK13: TButton;
    ButtonPrendreK14: TButton;
    ButtonPrendreK15: TButton;
    ButtonPrendreK16: TButton;
    ButtonPrendreK17: TButton;
    ButtonPrendreK18: TButton;
    ButtonPrendreK19: TButton;
    ButtonPrendreK2: TButton;
    ButtonPrendreK20: TButton;
    ButtonPrendreK21: TButton;
    ButtonPrendreK22: TButton;
    ButtonPrendreK23: TButton;
    ButtonPrendreK24: TButton;
    ButtonPrendreK25: TButton;
    ButtonPrendreK26: TButton;
    ButtonPrendreK27: TButton;
    ButtonPrendreK28: TButton;
    ButtonPrendreK29: TButton;
    ButtonPrendreK3: TButton;
    ButtonPrendreK30: TButton;
    ButtonPrendreK31: TButton;
    ButtonPrendreK32: TButton;
    ButtonPrendreK33: TButton;
    ButtonPrendreK34: TButton;
    ButtonPrendreK35: TButton;
    ButtonPrendreK36: TButton;
    ButtonPrendreK37: TButton;
    ButtonPrendreK38: TButton;
    ButtonPrendreK39: TButton;
    ButtonPrendreK4: TButton;
    ButtonPrendreK40: TButton;
    ButtonPrendreK41: TButton;
    ButtonPrendreK42: TButton;
    ButtonPrendreK43: TButton;
    ButtonPrendreK44: TButton;
    ButtonPrendreK45: TButton;
    ButtonPrendreK46: TButton;
    ButtonPrendreK47: TButton;
    ButtonPrendreK48: TButton;
    ButtonPrendreK49: TButton;
    ButtonPrendreK5: TButton;
    ButtonPrendreK50: TButton;
    ButtonPrendreK51: TButton;
    ButtonPrendreK52: TButton;
    ButtonPrendreK53: TButton;
    ButtonPrendreK54: TButton;
    ButtonPrendreK55: TButton;
    ButtonPrendreK56: TButton;
    ButtonPrendreK57: TButton;
    ButtonPrendreK58: TButton;
    ButtonPrendreK59: TButton;
    ButtonPrendreK6: TButton;
    ButtonPrendreK60: TButton;
    ButtonPrendreK61: TButton;
    ButtonPrendreK62: TButton;
    ButtonPrendreK63: TButton;
    ButtonPrendreK64: TButton;
    ButtonPrendreK7: TButton;
    ButtonPrendreK8: TButton;
    ButtonPrendreK9: TButton;
    ButtonRemetreK1: TButton;
    ButtonRemetreK10: TButton;
    ButtonRemetreK11: TButton;
    ButtonRemetreK12: TButton;
    ButtonRemetreK13: TButton;
    ButtonRemetreK14: TButton;
    ButtonRemetreK15: TButton;
    ButtonRemetreK16: TButton;
    ButtonRemetreK17: TButton;
    ButtonRemetreK18: TButton;
    ButtonRemetreK19: TButton;
    ButtonRemetreK2: TButton;
    ButtonRemetreK20: TButton;
    ButtonRemetreK21: TButton;
    ButtonRemetreK22: TButton;
    ButtonRemetreK23: TButton;
    ButtonRemetreK24: TButton;
    ButtonRemetreK25: TButton;
    ButtonRemetreK26: TButton;
    ButtonRemetreK27: TButton;
    ButtonRemetreK28: TButton;
    ButtonRemetreK29: TButton;
    ButtonRemetreK3: TButton;
    ButtonRemetreK30: TButton;
    ButtonRemetreK31: TButton;
    ButtonRemetreK32: TButton;
    ButtonRemetreK33: TButton;
    ButtonRemetreK34: TButton;
    ButtonRemetreK35: TButton;
    ButtonRemetreK36: TButton;
    ButtonRemetreK37: TButton;
    ButtonRemetreK38: TButton;
    ButtonRemetreK39: TButton;
    ButtonRemetreK4: TButton;
    ButtonRemetreK40: TButton;
    ButtonRemetreK41: TButton;
    ButtonRemetreK42: TButton;
    ButtonRemetreK43: TButton;
    ButtonRemetreK44: TButton;
    ButtonRemetreK45: TButton;
    ButtonRemetreK46: TButton;
    ButtonRemetreK47: TButton;
    ButtonRemetreK48: TButton;
    ButtonRemetreK49: TButton;
    ButtonRemetreK5: TButton;
    ButtonRemetreK50: TButton;
    ButtonRemetreK51: TButton;
    ButtonRemetreK52: TButton;
    ButtonRemetreK53: TButton;
    ButtonRemetreK54: TButton;
    ButtonRemetreK55: TButton;
    ButtonRemetreK56: TButton;
    ButtonRemetreK57: TButton;
    ButtonRemetreK58: TButton;
    ButtonRemetreK59: TButton;
    ButtonRemetreK6: TButton;
    ButtonRemetreK60: TButton;
    ButtonRemetreK61: TButton;
    ButtonRemetreK62: TButton;
    ButtonRemetreK63: TButton;
    ButtonRemetreK64: TButton;
    ButtonRemetreK7: TButton;
    ButtonRemetreK8: TButton;
    ButtonRemetreK9: TButton;
    ButtonStartStop: TButton;
    ComboBoxTimeout: TComboBox;
    EditPort: TEdit;
    GroupBoxK1: TGroupBox;
    GroupBoxK10: TGroupBox;
    GroupBoxK11: TGroupBox;
    GroupBoxK12: TGroupBox;
    GroupBoxK13: TGroupBox;
    GroupBoxK14: TGroupBox;
    GroupBoxK15: TGroupBox;
    GroupBoxK16: TGroupBox;
    GroupBoxK17: TGroupBox;
    GroupBoxK18: TGroupBox;
    GroupBoxK19: TGroupBox;
    GroupBoxK2: TGroupBox;
    GroupBoxK20: TGroupBox;
    GroupBoxK21: TGroupBox;
    GroupBoxK22: TGroupBox;
    GroupBoxK23: TGroupBox;
    GroupBoxK24: TGroupBox;
    GroupBoxK25: TGroupBox;
    GroupBoxK26: TGroupBox;
    GroupBoxK27: TGroupBox;
    GroupBoxK28: TGroupBox;
    GroupBoxK29: TGroupBox;
    GroupBoxK3: TGroupBox;
    GroupBoxK30: TGroupBox;
    GroupBoxK31: TGroupBox;
    GroupBoxK32: TGroupBox;
    GroupBoxK33: TGroupBox;
    GroupBoxK34: TGroupBox;
    GroupBoxK35: TGroupBox;
    GroupBoxK36: TGroupBox;
    GroupBoxK37: TGroupBox;
    GroupBoxK38: TGroupBox;
    GroupBoxK39: TGroupBox;
    GroupBoxK4: TGroupBox;
    GroupBoxK40: TGroupBox;
    GroupBoxK41: TGroupBox;
    GroupBoxK42: TGroupBox;
    GroupBoxK43: TGroupBox;
    GroupBoxK44: TGroupBox;
    GroupBoxK45: TGroupBox;
    GroupBoxK46: TGroupBox;
    GroupBoxK47: TGroupBox;
    GroupBoxK48: TGroupBox;
    GroupBoxK49: TGroupBox;
    GroupBoxK5: TGroupBox;
    GroupBoxK50: TGroupBox;
    GroupBoxK51: TGroupBox;
    GroupBoxK52: TGroupBox;
    GroupBoxK53: TGroupBox;
    GroupBoxK54: TGroupBox;
    GroupBoxK55: TGroupBox;
    GroupBoxK56: TGroupBox;
    GroupBoxK57: TGroupBox;
    GroupBoxK58: TGroupBox;
    GroupBoxK59: TGroupBox;
    GroupBoxK6: TGroupBox;
    GroupBoxK60: TGroupBox;
    GroupBoxK61: TGroupBox;
    GroupBoxK62: TGroupBox;
    GroupBoxK63: TGroupBox;
    GroupBoxK64: TGroupBox;
    GroupBoxK7: TGroupBox;
    GroupBoxK8: TGroupBox;
    GroupBoxK9: TGroupBox;
    IdTCPServer1: TIdTCPServer;
    LabelPort: TLabel;
    LabelPort1: TLabel;
    PanelLig1: TPanel;
    PanelLig2: TPanel;
    PanelLig3: TPanel;
    PanelLig4: TPanel;
    PanelLig5: TPanel;
    PanelLig6: TPanel;
    PanelLig7: TPanel;
    PanelLig8: TPanel;
    PanelTop: TPanel;
    ShapeLedK10: TShape;
    ShapeLedK11: TShape;
    ShapeLedK12: TShape;
    ShapeLedK13: TShape;
    ShapeLedK14: TShape;
    ShapeLedK15: TShape;
    ShapeLedK16: TShape;
    ShapeLedK17: TShape;
    ShapeLedK18: TShape;
    ShapeLedK19: TShape;
    ShapeLedK2: TShape;
    ShapeLedK20: TShape;
    ShapeLedK21: TShape;
    ShapeLedK22: TShape;
    ShapeLedK23: TShape;
    ShapeLedK24: TShape;
    ShapeLedK25: TShape;
    ShapeLedK26: TShape;
    ShapeLedK27: TShape;
    ShapeLedK28: TShape;
    ShapeLedK29: TShape;
    ShapeLedK3: TShape;
    ShapeLedK30: TShape;
    ShapeLedK31: TShape;
    ShapeLedK32: TShape;
    ShapeLedK33: TShape;
    ShapeLedK34: TShape;
    ShapeLedK35: TShape;
    ShapeLedK36: TShape;
    ShapeLedK37: TShape;
    ShapeLedK38: TShape;
    ShapeLedK39: TShape;
    ShapeLedK4: TShape;
    ShapeLedK40: TShape;
    ShapeLedK41: TShape;
    ShapeLedK42: TShape;
    ShapeLedK43: TShape;
    ShapeLedK44: TShape;
    ShapeLedK45: TShape;
    ShapeLedK46: TShape;
    ShapeLedK47: TShape;
    ShapeLedK48: TShape;
    ShapeLedK49: TShape;
    ShapeLedK5: TShape;
    ShapeLedK50: TShape;
    ShapeLedK51: TShape;
    ShapeLedK52: TShape;
    ShapeLedK53: TShape;
    ShapeLedK54: TShape;
    ShapeLedK55: TShape;
    ShapeLedK56: TShape;
    ShapeLedK57: TShape;
    ShapeLedK58: TShape;
    ShapeLedK59: TShape;
    ShapeLedK6: TShape;
    ShapeLedK60: TShape;
    ShapeLedK61: TShape;
    ShapeLedK62: TShape;
    ShapeLedK63: TShape;
    ShapeLedK64: TShape;
    ShapeLedK7: TShape;
    ShapeLedK8: TShape;
    ShapeLedK9: TShape;
    ShapeStatut: TShape;
    ShapeLedK1: TShape;
    StaticTextData: TStaticText;
    Timer1: TTimer;
    procedure ButtonPrendreClick(Sender: TObject);
    procedure ButtonRemetreClick(Sender: TObject);
    procedure ButtonStartStopClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure IdTCPServer1Execute(AContext: TIdContext);
    procedure ShapeLedK1ChangeBounds(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    tabkeytimer:array[1..nbekey] of integer;
    lasttime,newtime:tdatetime;
    procedure DecTime;
    procedure prepareallkey(keypresent:boolean);
    procedure prepareonekey(numkey:integer;keypresent:boolean);
    procedure DisconnectAllClient(p_message : string);
    function  crc16reverse(Buffer:TidBytes;Polynom,Initial:Cardinal):Cardinal;
    function  mkstatus(c1,c2:byte):tidbytes;
    function  mkparam(c1,c2:byte):tidbytes;
    procedure FreeKey(numkey:byte);
  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

//CRC à la mode Monthghetti
function TForm1.crc16reverse(Buffer:TidBytes;Polynom,Initial:Cardinal):Cardinal;
var
  i,j: Integer;
begin
Result:=Initial;
for i:=1 to Length(Buffer) do
  begin
    Result:=Result xor buffer[i];
    for j:=0 to 7 do begin
      if (Result and $0001)<>0 then Result:=(Result shr 1) xor Polynom
      else Result:=Result shr 1;
      end;
  end;
end;


procedure TForm1.FormCreate(Sender: TObject);
begin
  ShapeStatut.Brush.color:=clred;;
  ButtonStartStop.Caption:='Start';
  ButtonStartStop.enabled:=True;
  Editport.Text:='4925';
  Editport.enabled:=True;
  StaticTextData.Caption:='';
  prepareallkey(True);
end;






function Tform1.mkstatus(c1,c2:byte):tidbytes;
var i,lig:byte;
    v:string;
begin
    v:='';
    for i:=1 to NBEKEY do v:=v+'N';
    for i:=1 to NBEKEY do
       begin
          if Tshape(FindComponent('ShapeLedK'+inttostr(i))).Brush.color<>clred then v[i]:='Y';
       end;
    setlength(result,10);
    for i:=0 to High(result) do result[i]:=0;
    result[0]:=c1;
    result[1]:=c2;

    for lig:=1 to round(NBEKEY/8) do
       begin
          for i:=(lig-1)*8 to (lig*8)-1 do
             begin
                if v[i+1]='N' then
                   result[lig-1+2]:= result[lig-1+2]+floor(power(2,i-(lig-1)*8));
             end;
       end;
    {
    i:= 56;
    while (( i < length(v)) and ( i < 64) and (i < NBEKEY)) do
       begin
            if v[i+1] = 'N' then
                    o7:= o7 + floor(power(2,i - 56));
            i:= i + 1;
       end;
     }
end;


function Tform1.mkparam(c1,c2:byte):tidbytes;
var o1,o2,o3,o4,o5:byte;
    v:string;
begin
    o1:=strtoint(comboboxtimeout.items[comboboxtimeout.itemindex]);
    o2:=8;
    o3:=7;
    o4:=2;
    o5:=60;
    setlength(result,7);
    result[0]:=c1;
    result[1]:=c2;
    result[2]:=o1;
    result[3]:=o2;
    result[4]:=o3;
    result[5]:=o4;
    result[6]:=o5;
end;

procedure TForm1.DecTime;
var i:integer;
    diff:int64;
begin
    newtime:=Time;
    for i:= 1 to nbekey do
       begin
          if (Tshape(FindComponent('ShapeLedK'+inttostr(i))).Brush.color=clGreen) then
          begin
             diff:=MilliSecondsBetween(newtime,lasttime);
            if tabkeytimer[i]>0 then tabkeytimer[i]:=tabkeytimer[i]-diff;
            if (tabkeytimer[i]<=0) and (Tshape(FindComponent('ShapeLedK'+inttostr(i))).Brush.color=clGreen) then
               begin
                  Tshape(FindComponent('ShapeLedK'+inttostr(i))).Brush.color:=clwhite;
                  Tshape(FindComponent('ShapeLedK'+inttostr(i))).refresh;
                  Tbutton(FindComponent('ButtonPrendreK'+inttostr(i))).Enabled:=False;
                  tabkeytimer[i]:=0;
               end;
          end;
       end;
    lasttime:=Newtime;

end;


//Ca va aller très vite
//au clavier, je donne 30 ms pour fournir toutes les données
//mais byte_buffer peut récupérer plus d'un octet
procedure TForm1.IdTCPServer1Execute(AContext: TIdContext);
var
  i:integer;
  s:string;
  longueur:int64;
  idstream:tmemorystream;
  byte_buffer:TidBytes;
  crc16,crcmsg:cardinal;
  msg:TidBytes;
  numkey:byte;
begin

  AContext.Connection.IOHandler.ReadBytes(byte_buffer, -1, False);
  s:='';
  for i:=low(byte_buffer) to high(byte_buffer) do
     s:=s+inttohex(byte_buffer[i],2)+' ';
  if s<>'' then StaticTextData.caption:=s;

  //Traitement
  if high(byte_buffer)<0 then exit;
  if (byte_buffer[0]<>$10) then exit;
  if high(byte_buffer)<1 then exit;
  if (byte_buffer[1]<>$01) and (byte_buffer[1]<>$02) and (byte_buffer[0]<>$FF) then exit;
  if high(byte_buffer)<2 then exit;
  //Liberation de clé
  if (byte_buffer[1]=$01) then
     begin
        if high(byte_buffer)<2 then exit;
        numkey:=byte_buffer[2];
        //crc16:=byte_buffer[3]*255+byte_buffer[4];
        setlength(msg,3);
        msg[0]:=byte_buffer[0];
        msg[1]:=byte_buffer[1];
        msg[2]:=byte_buffer[2];
        crcmsg:=crc16reverse(msg,POLY,INIT);
        //if crcmsg<>crc16 then
        //   statictextdata.caption:=inttohex(crc16,4)+'<>'+inttohex(crcmsg,4);
        msg:=mkstatus(byte_buffer[0],byte_buffer[1]);
        crcmsg:=crc16reverse(msg,POLY,INIT);
        AContext.Connection.IOHandler.Write(msg,-1,0);
        s:='';
        for i:=low(msg) to high(msg) do
           s:=s+inttohex(msg[i],2)+' ';
        if s<>'' then StaticTextData.caption:=s;
        FreeKey(numkey+1);
     end;

  //Statut
  if (byte_buffer[1]=$02) then
     begin
        if high(byte_buffer)<2 then exit;
        //crc16:=byte_buffer[2]*255+byte_buffer[3];
        setlength(msg,3);
        msg[0]:=byte_buffer[0];
        msg[1]:=byte_buffer[1];
        msg[2]:=byte_buffer[2];
        crcmsg:=crc16reverse(msg,POLY,INIT);
        //if crcmsg<>crc16 then
        //   statictextdata.caption:=inttohex(crc16,4)+'<>'+inttohex(crcmsg,4);
        msg:=mkstatus(byte_buffer[0],byte_buffer[1]);
        crcmsg:=crc16reverse(msg,POLY,INIT);
        //setlength(msg,high(msg)+3);
        //msg[high(msg)]:=div(crcmsg,256);
        //msg[high(msg)]:=mod(crcmsg,256)
        AContext.Connection.IOHandler.Write(msg,-1,0);
        s:='';
        for i:=low(msg) to high(msg) do
           s:=s+inttohex(msg[i],2)+' ';
        if s<>'' then StaticTextData.caption:=s;
     end;

  //Param
  if (byte_buffer[1]=$FF) then
     begin
        if high(byte_buffer)<2 then exit;
        //crc16:=byte_buffer[2]*255+byte_buffer[3];
        msg[0]:=byte_buffer[0];
        msg[1]:=byte_buffer[1];
        msg[2]:=byte_buffer[2];
        //if crcmsg<>crc16 then
        //   statictextdata.caption:=inttohex(crc16,4)+'<>'+inttohex(crcmsg,4);
        msg:=mkparam(byte_buffer[0],byte_buffer[1]);
        crcmsg:=crc16reverse(msg,POLY,INIT);
        //setlength(msg,high(msg)+3);
        //msg[high(msg)]:=div(crcmsg,256);
        //msg[high(msg)]:=mod(crcmsg,256)
        AContext.Connection.IOHandler.Write(msg,-1,0);
        s:='';
        for i:=low(msg) to high(msg) do
           s:=s+inttohex(msg[i],2)+' ';
        if s<>'' then StaticTextData.caption:=s;
     end;
end;

procedure TForm1.ShapeLedK1ChangeBounds(Sender: TObject);
begin
  Statictextdata.caption:=Statictextdata.caption+' ';
end;



procedure TForm1.Timer1Timer(Sender: TObject);
begin
   DecTime;
end;












procedure TForm1.ButtonStartStopClick(Sender: TObject);
var n:integer;
begin
  lasttime:=Time;
  newtime:=Time;
  if idtcpserver1.Active then
     begin
        ShapeStatut.Brush.color:=clred;;
        ButtonStartStop.Caption:='Start';
        Editport.enabled:=True;
        idtcpserver1.OnDisconnect:=nil;
        DisconnectAllClient('Good Bye');
        try
           idtcpserver1.active:=false;
        except on e:exception do
           begin
               showmessage(E.Message);
           end;
        end;
        Exit;
     end;
  if not trystrtoint(editport.text,n) then
     begin
       showmessage('Numéro de port incorrect');
       exit;
     end;
  if (n<1000) or (n>65535) then
     begin
       showmessage('Numéro de port incorrect attendu : 1000...65535');
       exit;
     end;
  if not idtcpserver1.Active then
     begin
        StaticTextData.Caption:='';
        idtcpserver1.Bindings.Clear;
        idtcpserver1.Bindings.Add.Port:=n;
        ButtonStartStop.Caption:='Stop';
        Editport.enabled:=False;
        idtcpserver1.Active:=True;;
        ShapeStatut.Brush.color:=clgreen;;
        Exit;
     end;

end;

procedure TForm1.ButtonPrendreClick(Sender: TObject);
begin
   TButton(FindComponent('ButtonPrendreK'+inttostr((sender as TButton).tag))).enabled:=False;
   TButton(FindComponent('ButtonRemetreK'+inttostr((sender as TButton).tag))).enabled:=True;
   Tshape(FindComponent('ShapeLedK'+inttostr((sender as TButton).tag))).Brush.color:=clred;
   tabkeytimer[(sender as TButton).tag]:=0;
end;

procedure TForm1.ButtonRemetreClick(Sender: TObject);
begin
  TButton(FindComponent('ButtonPrendreK'+inttostr((sender as TButton).tag))).enabled:=False;
  TButton(FindComponent('ButtonRemetreK'+inttostr((sender as TButton).tag))).enabled:=False;
  Tshape(FindComponent('ShapeLedK'+inttostr((sender as TButton).tag))).Brush.color:=clWhite;
  tabkeytimer[(sender as TButton).tag]:=0;
end;





procedure TForm1.prepareallkey(keypresent:boolean);
var i:integer;
begin
   for i:=1 to NBEKEY do prepareonekey(i,keypresent);
end;

procedure TForm1.prepareonekey(numkey:integer;keypresent:boolean);
begin
  TButton(FindComponent('ButtonPrendreK'+inttostr(numkey))).enabled:=False;
  TButton(FindComponent('ButtonPrendreK'+inttostr(numkey))).tag:=numkey;
  TButton(FindComponent('ButtonRemetreK'+inttostr(numkey))).enabled:=Not keypresent;
  TButton(FindComponent('ButtonRemetreK'+inttostr(numkey))).tag:=numkey;
  Tshape(FindComponent('ShapeLedK'+inttostr(numkey))).ShowHint:=True;
  Tshape(FindComponent('ShapeLedK'+inttostr(numkey))).tag:=numkey;
  TButton(FindComponent('ButtonPrendreK'+inttostr(numkey))).Onclick:=@ButtonPrendreClick;
  TButton(FindComponent('ButtonRemetreK'+inttostr(numkey))).Onclick:=@ButtonRemetreClick;
  if keypresent then
     begin
        Tshape(FindComponent('ShapeLedK'+inttostr(numkey))).Brush.color:=clwhite;
        Tshape(FindComponent('ShapeLedK'+inttostr(numkey))).Hint:='Clé '+inttostr(numkey)+' présente';
        tabkeytimer[numkey]:=0;
     end
  else
    begin
       Tshape(FindComponent('ShapeLedK'+inttostr(numkey))).Brush.color:=clRed;
       Tshape(FindComponent('ShapeLedK'+inttostr(numkey))).Hint:='Clé '+inttostr(numkey)+' absente';
    end;

end;

// *****************************************************************************
//   PROCEDURE : DisconnectAllClient()
//               BROADCAST A MESSAGE TO ALL CLIENTS CONNECTED
// *****************************************************************************
procedure TForm1.DisconnectAllClient(p_message : string);
var
    tmpList      : TList;
    contexClient : TidContext;
begin
    tmpList  := IdTCPServer1.Contexts.LockList;
    try
        while (tmpList.Count>0) do
           begin
              contexClient := TidContext(tmpList[0]);
              if p_message<>'' then contexClient.Connection.IOHandler.WriteLn(p_message);
              contexClient.Connection.Disconnect();
              tmpList.Delete(0);
           end;
        IdTCPServer1.Contexts.UnlockList;
    finally
    end;
end;

procedure Tform1.FreeKey(numkey:byte);
var FTimer:TTimer;
begin
  //Ne pas libérer unbe clé qui n'existe pas
  if numkey>NBEKEY then exit;
  tabkeytimer[numkey]:=strtoint(comboboxtimeout.items[comboboxtimeout.Itemindex])*1000;
  Tshape(FindComponent('ShapeLedK'+inttostr(numkey))).Brush.color:=ClGreen;
  Tbutton(FindComponent('ButtonPrendreK'+inttostr(numkey))).Enabled:=true;
  //Parce que sur l'armoire à clés d'hispano, le casier s'ouvre instantanément
  Tbutton(FindComponent('ButtonPrendreK'+inttostr(numkey))).Click;
end;

end.

