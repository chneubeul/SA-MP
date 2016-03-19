/****************************************************************************************************
 *                                                                                                  *
 * FullServer Objects Loader v3.1                                                                   *
 * Authored by eider                                                                                *
 * Update by Abyss Morgan                                                                           *
 *                                                                                                  *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/filterscripts                         *
 *                                                                                                  *
 ****************************************************************************************************/

/*
Dozwolone formaty

CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid);
CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid);
CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, playerid);
CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, playerid, Float:streamdistance);
CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid, interiorid, playerid, Float:streamdistance, Float:drawdistance);
*/

#define LOG_FILE		"objsX.log"
#define MAX_FIND_OBJ	(1000)

#define COLOR_ERROR		(0xB01010FF)

#include <a_samp>
#include <streamer>
#include <sscanf2>
#include <zcmd>
#define FIX_OBJECTS
#include <SAM/StreamerFunction>
#include <SAM/BitFunctions>
#include <SAM/3DTryg>
#include <SAM/ADM>
#include <SAM/DoT>
#include <SAM/BINLDR>

//Check StreamerFunction.inc
#if !defined _streamer_spec
	#error You need StreamerFunction.inc v2.1b
#elseif !defined Streamer_Spec_Version
	#error Update you StreamerFunction.inc to v2.1b
#elseif (Streamer_Spec_Version < 20102)
	#error Update you StreamerFunction.inc to v2.1b
#endif

//Check 3DTryg.inc
#if !defined _3D_Tryg
	#error You need 3DTryg.inc v2.1b
#elseif !defined Tryg3D_Version
	#error Update you 3DTryg.inc to v2.1b
#elseif (Tryg3D_Version < 20102)
	#error Update you 3DTryg.inc to v2.1b
#endif

//Check Version ADM.inc
#if !defined _adm_encryption
	#error You need ADM.inc v1.9
#elseif !defined ADM_Encryption_Version
	#error Update you ADM.inc to v1.9
#elseif (ADM_Encryption_Version < 10901)
	#error Update you ADM.inc to v1.9
#endif

//Check Version DoT.inc
#if !defined _DoT_Loader
	#error You need DoT.inc v1.3
#elseif !defined DoT_Loader_Version
	#error Update you DoT.inc to v1.3
#elseif (DoT_Loader_Version < 10301)
	#error Update you DoT.inc to v1.3
#endif

//Check Version BINLDR.inc
#if !defined _Bin_Loader
	#error You need BINLDR.inc v2.0
#elseif !defined Bin_Loader_Version
	#error Update you BINLDR.inc to v2.0
#elseif (Bin_Loader_Version < 20001)
	#error Update you BINLDR.inc to v2.0
#endif

new pliki[][32] = {
	"objectsfile1.txt",
	"objectsfile2.txt"
};

new DoTFile[][32] = {
	"empty.dot"
};

new BinIMGFile[][32] = {
	"empty.bin"
};

WriteLog(file[],string[]){
	static wl_date[3],wl_time[3],wl_str[512],wl_file[64];
	getdate(wl_date[0],wl_date[1],wl_date[2]);
   	gettime(wl_time[0],wl_time[1],wl_time[2]);
   	format(wl_str,sizeof wl_str,"[%02d.%02d.%02d %02d:%02d:%02d] %s\r\n",wl_date[0],wl_date[1],wl_date[2],wl_time[0],wl_time[1],wl_time[2],string);
	format(wl_file,sizeof wl_file,"/%s",file);
	if(!fexist(wl_file)){
		new File:cfile = fopen(wl_file,io_readwrite);
		fwrite(cfile,"");
		fclose(cfile);
	}
	new File:flog = fopen(wl_file,io_append);
	fwrite(flog,wl_str);
	fclose(flog);
	return 1;
}

new Text3D:FindObjLabel[MAX_FIND_OBJ], bool:FindObj = false;

stock FindDynamicObject(playerid, Float:findradius, Float:streamdistance = 20.0){
	new buffer[256], szLIST[768], cnt = 0, Float:px, Float:py, Float:pz,
	moid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, vw, int, Float:sd, Float:dd;
	
	GetPlayerPos(playerid,px,py,pz);
	ForDynamicObjects(i){
		if(cnt >= MAX_FIND_OBJ) break;
		if(IsValidDynamicObject(i)){
			GetDynamicObjectPos(i,x,y,z);
			new Float:distance = GetDistanceBetweenPoints3D(x,y,z,px,py,pz);
			if(distance <= findradius){
				vw = GetDynamicObjectVW(i);
				int = GetDynamicObjectINT(i);
				moid = GetDynamicObjectModel(i);
				GetDynamicObjectRot(i,rx,ry,rz);
				GetDynamicObjectSD(i,sd);
				GetDynamicObjectDD(i,dd);
				szLIST = "";
				format(buffer,sizeof buffer,"{89C1FA}Object: {00AAFF}(%d) {89C1FA}Model: {00AAFF}(%d) {89C1FA}Stream: {00AAFF}(%d %d %.0f %.0f)\n",i,moid,vw,int,sd,dd);
				strcat(szLIST,buffer);
				format(buffer,sizeof buffer,"{89C1FA}Pos: {00AAFF}(%.7f,%.7f,%.7f,%.7f,%.7f,%.7f)",x,y,z,rx,ry,rz);
				strcat(szLIST,buffer);
				FindObjLabel[cnt] = CreateDynamic3DTextLabel(szLIST,0x89C1FAFF,x,y,z+0.2,streamdistance,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,-1,-1,-1,streamdistance);
				cnt++;
			}
		}
	}
}

stock RemoveFindDynamicObjectLabel(){
	for(new i = 0; i < MAX_FIND_OBJ; i++){
		if(IsValidDynamic3DTextLabel(FindObjLabel[i])) DestroyDynamic3DTextLabel(FindObjLabel[i]);
	}
}

CMD:addobjinfo(playerid,params[]){
	if(!IsPlayerAdmin(playerid)) return 0;
	if(FindObj) return SendClientMessage(playerid,COLOR_ERROR,"››› Funkcja aktywna, wpisz /delobjinfo");
	if(isnull(params)) return SendClientMessage(playerid,COLOR_ERROR,"››› U¿ywaj: /addobjinfo <streamdistance (1-100)> <find radius>");
	new Float:sd, Float:findr;
	sscanf(params,"ff",sd,findr);
	if(findr < 1.0) findr = 20.0;
	if(sd < 1.0 || sd > 100.0) return SendClientMessage(playerid,COLOR_ERROR,"››› Stream distance musi mieœciæ siê w przedziale 1-100");
	new buffer[256];
	format(buffer,sizeof buffer,"Opis obiektów zosta³ w³¹czony, zasiêg %.0fm",sd);
	SendClientMessage(playerid,0xFFFFFFFF,buffer);
	FindDynamicObject(playerid,findr,sd);
	FindObj = true;
	return 1;
}

CMD:delobjinfo(playerid){
	if(!IsPlayerAdmin(playerid)) return 0;
	if(!FindObj) return SendClientMessage(playerid,COLOR_ERROR,"››› Funkcja nieaktywna");
	RemoveFindDynamicObjectLabel();
	FindObj = false;
	SendClientMessage(playerid,0xFFFFFFFF,"Usuniêto wszystkie podpisy obiektów");
	return 1;
}

//objstatus by Abyss Morgan
CMD:objstatus(playerid){
	if(!IsPlayerAdmin(playerid)) return 0;
	new pVW, pINT, cnt = 0, vis, buffer[200], oVW, oINT, tmp = 0;
	pVW = GetPlayerVirtualWorld(playerid);
	pINT = GetPlayerInterior(playerid);
	vis = Streamer_CountVisibleItems(playerid,STREAMER_TYPE_OBJECT);
	ForDynamicObjects(i){
		if(IsValidDynamicObject(i)){
			tmp = 0;
			oVW = GetDynamicObjectVW(i);
			oINT = GetDynamicObjectINT(i);
			if((oVW == -1 || oVW == pVW) && (oINT == -1 || oINT == pINT)) tmp = 1;
			if((oVW == -1 && pINT == oINT) || (oINT == -1 && pVW == pVW)) tmp = 1;
			if(tmp == 1) cnt++;
		}
	}
	format(buffer,sizeof buffer,"[Obiekty] Widocznych: %d, Œwiat VW %d INT %d: %d, Wszystkich: %d, Maksymalnie: %d, Statyczne: %d",vis,pVW,pINT,cnt,CountDynamicObjects(),GetDynamicObjectPoolSize()+1,CountObjects());
	SendClientMessage(playerid,0xFFFFFFFF,buffer);
	return 1;
}

public OnFilterScriptInit(){
	new silo = GetTickCount(), buf[255], line[255], File:olist, cnt = 0, lnum = 0, ecnt = 0, totalcnt = 0;
	SendClientMessageToAll(0xFF0000FF,"[IMPORTANT] Trwa prze³adowywanie obiektów...");
	WriteLog(LOG_FILE," ");
	WriteLog(LOG_FILE,"[IMPORTANT] Trwa przeladowywanie obiektow...");
	WriteLog(LOG_FILE," ");
	for(new i=0;i<sizeof(pliki);i++){
		if(fexist(pliki[i])){
			olist = fopen(pliki[i], io_read);
			cnt = 0, lnum=0;
			while(fread(olist, line)){
				lnum++;
				if(line[0]!='/' && strfind(line,"CreateDynamicObject",true)!=-1){
					new objectid, Float:X, Float:Y, Float:Z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 200.0, Float:drawdistance = 0.0, Float:nul;
					if(sscanf(line,"p<,>'('ifffffP<,)>fP<,)>D(-1)D(-1)D(-1)F(-1)F(0)p<)>F(0)", objectid, X, Y, Z, rx, ry, rz, worldid, interiorid, playerid, streamdistance, drawdistance, nul)){
						if(streamdistance == -1) streamdistance = CalculateObjectDistance(objectid);
						CreateDynamicObject(objectid,X,Y,Z,rx,ry,rz,worldid,interiorid,playerid,streamdistance,drawdistance);
						cnt++;
					} else {
						ecnt++;
						format(buf,sizeof buf,"%s, linia %d, blad w parsowaniu: %s",pliki[i],lnum,line);
						WriteLog(LOG_FILE,buf);
					}
				}
			}
			totalcnt += cnt;
			fclose(olist);
			format(line,sizeof line,"%s, linii: %d, obiektow: %d",pliki[i],lnum,cnt);
			WriteLog(LOG_FILE,line);
		}
	}
	for(new i = 0, j = sizeof(DoTFile); i < j; i++){
		if(fexist(DoTFile[i])){
			LoadDoTMap(DoTFile[i],totalcnt);
		}
	}
	for(new i = 0, j = sizeof(BinIMGFile); i < j; i++){
		if(fexist(BinIMGFile[i])){
			LoadBinaryObjectIMG(BinIMGFile[i],totalcnt);
		}
	}
	if(ecnt > 0){
		WriteLog(LOG_FILE," ");
		format(buf,sizeof buf,"Zaladowano %d obiektow w %d ms, wykryto %d bledow",totalcnt,GetTickCount()-silo,ecnt);
		print(buf);
		WriteLog(LOG_FILE,buf);
		WriteLog(LOG_FILE," ");
	} else {
		WriteLog(LOG_FILE," ");
		format(buf,sizeof buf,"Zaladowano %d obiektow w %d ms",totalcnt,GetTickCount()-silo);
		print(buf);
		WriteLog(LOG_FILE,buf);
		WriteLog(LOG_FILE," ");
	}
	return 1;
}

//EOF
