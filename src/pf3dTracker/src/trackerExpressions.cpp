#include <highgui.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/FrameGrabberInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/Drivers.h>

#include <iCub/trackerExpressions.hpp>




//constructor
TrackerExpressions::TrackerExpressions()
{
    ;
}



//destructor
TrackerExpressions::~TrackerExpressions()
{
    cout<<"oh my god! they killed kenny!    you bastards!\n";
}



//member function that set the object up.
bool TrackerExpressions::open(Searchable& config)
{

    //***********************************
    //Read options from the command line.
    //***********************************
    // pass configuration over to bottle
    Bottle botConfig(config.toString().c_str());
    botConfig.setMonitor(config.getMonitor()); //is this needed?

    _inputPortName = botConfig.check("inputPort",
                                       Value("/icub/trackerExpressions/in"),
                                       "Input port (string)").asString();
    _inputPort.open(_inputPortName);

    _outputPortName = botConfig.check("outputPort",
                                       Value("/icub/trackerExpressions/out"),
                                       "Output port (string)").asString();
    _outputPort.open(_outputPortName);

    _counter=0;
    return true;  //the object was set up successfully.
}



//member that closes the object.
bool TrackerExpressions::close()
{
    _inputPort.close();
    _outputPort.close();
    return true;
}

//member that closes the object.
bool TrackerExpressions::interruptModule()
{
    _inputPort.interrupt();
    _outputPort.interrupt();
    return true;
}


//member that is repeatedly called by YARP, to give this object the chance to do something.
//should this function return "false", the object would be terminated.
//I already have one image, when I get here (I either acquire it in the initialization method or in the end of this same method).
bool TrackerExpressions::updateModule()
{
     Bottle *tracker=_inputPort.read(false);

       if(tracker!=NULL)
       {
	  //get the flag that tells whether the likelihood is above the threshold.
	  if((tracker->get(6)).asInt()==1)
	  {
	   //cout<<"A\n";   
           Bottle& output=_outputPort.prepare();
           output.clear();
           output.fromString("set all hap");
           _outputPort.write();
           _counter=0;
	  }
	  else
	  {
	      
           _counter++;
	   if(_counter>10)
           {
	   //cout<<"B\n";   
           Bottle& output=_outputPort.prepare();
           output.clear();
           output.fromString("set all ang");
           _outputPort.write();
           
           }
	  }
       }
	//else
        //{
        //  cout<<"C\n";   
        //}


    yarp::os::Time::delay(0.05);
    return true; //continue. //in this case it means everything is fine.
}










































// 	string stringa;
// 	int position;
// 	string a, b;
// 	a=";";
// 	b="\n";
//        Bottle * head=_inputHeadPort.read(false);
//        if(head!=NULL)
//        {
// 	  //get data and convert from degrees to radians
// 	  head0=(head->get(0)).asDouble()*M_PI/180;
// 	  head1=(head->get(1)).asDouble()*M_PI/180;
// 	  head2=(head->get(2)).asDouble()*M_PI/180;
// 	  head3=(head->get(3)).asDouble()*M_PI/180;
// 	  head4=(head->get(4)).asDouble()*M_PI/180;
// 	  head5=(head->get(5)).asDouble()*M_PI/180;
// 	  //cout<<"Received head values: "<<head0<<" "<<head1<<" "<<head2<<" "<<head3<<" "<<head4<<" "<<head5<<endl;
// 	  receivedHead = true;
//        }
// 
//        Bottle * torso=_inputTorsoPort.read(false);
//        if(torso!=NULL)
//        {
// 	  //get data and convert from degrees to radians
// 	  torso0=(torso->get(0)).asDouble()*M_PI/180;
// 	  torso1=(torso->get(1)).asDouble()*M_PI/180;
// 	  torso2=(torso->get(2)).asDouble()*M_PI/180;
// 	  //cout<<"received torso values: "<<torso0<<" "<<torso1<<" "<<torso2<<endl;
// 	  receivedTorso = true;
//        }
// 
//        Bottle * ballPositionIn=_inputBallPositionPort.read(false);
//        if(ballPositionIn!=NULL)
//        {
// 	  //get the data and convert millimeters to meters
// 	  ballPositionInX=(ballPositionIn->get(0)).asDouble()/1000;
// 	  ballPositionInY=(ballPositionIn->get(1)).asDouble()/1000;
// 	  ballPositionInZ=(ballPositionIn->get(2)).asDouble()/1000;
// 	  ballPositionInGood=(ballPositionIn->get(6)).asDouble();
// 	  //cout<<"Received ballPositionIn values: "<<ballPositionInX<<" "<<ballPositionInY<<" "<<ballPositionInZ<<" "<<ballPositionInGood<<endl;
// 	  receivedBallPosition = true;
//        }
// 
//       if(receivedHead && receivedTorso && receivedBallPosition)
//       {
// 	//DO THE PROCESSING AND THE OUTPUT
// 
// 
// 	//cout<<"Received head values: "<<head0<<" "<<head1<<" "<<head2<<" "<<head3<<" "<<head4<<" "<<head5<<endl;
//         //cout<<"received torso values: "<<torso0<<" "<<torso1<<" "<<torso2<<endl;
// 	//cout<<"Received ballPositionIn values: "<<ballPositionInX<<" "<<ballPositionInY<<" "<<ballPositionInZ<<" "<<ballPositionInGood<<endl;
// 	//need to check the order of these parameters ??? !!! WARNING
// 
// 
// 
//     //Vector v(8);
// 
//     
//     v[0]=torso2;
//     v[1]=torso1;
//     v[2]=torso0;
//     v[3]=head0;
//     v[4]=head1;
//     v[5]=head2;
//     v[6]=head3;
//     //v[7]=head4+head5; //left eye. VERSION BY UGO.
//     //v[7]=(head4+head5)/2; //left eye. VERSION BY MANUEL, WORKED BEFORE THE CHANGE IN THE CONFIGURATION OF THE ENCODER TICKS.
//     v[7]=head4+head5/2; //left eye, VERSION ACCORDING TO THE WIKI: http://eris.liralab.it/wiki/Vergence%2C_Version_and_Disparity
// 
//     //Matrix transformation;
//     transformation = chainEyeL.getH(v);
//     stringa= transformation.toString();
//     position =stringa.find(a,0);
//     stringa.replace( position, 1, b, 0, 2);
//     position =stringa.find(a,0);
//     stringa.replace( position, 1, b, 0, 2);
//     position =stringa.find(a,0);
//     stringa.replace( position, 1, b, 0, 2);
// 	counter++;
// 	if(counter==10)
// 	{	
//                 cout<<"Torso values: "<<torso0<<" "<<torso1<<" "<<torso2<<endl;
//                 cout<<"Head values: "<<head0<<" "<<head1<<" "<<head2<<" "<<head3<<" "<<head4<<" "<<head5<<endl;
// 		cout<<"Matrix:\n";
//                 cout<<stringa<<endl;
// 		counter=0;
// 	}
// 	//Vector eyeBallPosition(4);
// 	//need to check this reference frame of the eye ??? !!! WARNING
// 	eyeBallPosition[0]=ballPositionInX;
// 	eyeBallPosition[1]=ballPositionInY;
// 	eyeBallPosition[2]=ballPositionInZ;
// 	eyeBallPosition[3]=1;
// 
// 	//Vector rootBallPosition(4);
// 	rootBallPosition=transformation*eyeBallPosition;
// 	//cout<<"Output:\n";
//         //cout<<rootBallPosition.toString()<<endl;
// 	//yarp::os::Time::delay(5);
// 	if(rootBallPosition[0]<-0.25)
//         {
// 		positionConsideredSafe = true;
// 	}
// 	else
//         {
// 		positionConsideredSafe = false;
// 	}
// 
// 
// 	//send the data on the output port, ONLY if likelihood is over threshold (flag==1)
// 	if(ballPositionInGood && positionConsideredSafe)
// 	{
// 	  Bottle& output=_outputBallPositionPort.prepare();
// 	  output.clear();
// 	  output.addDouble(rootBallPosition[0]);
// 	  output.addDouble(rootBallPosition[1]);
// 	  output.addDouble(rootBallPosition[2]);
// 	  _outputBallPositionPort.write();
// 	}
// 
// 
//       }
//       else
//       {
// 	//YOU DO NOT HAVE ENOUGH DATA: DO NOTHING.
//       }
//      
//       yarp::os::Time::delay(0.05);
// 
// //     double K=0.02;
// //     double horizontalError, horizontalSpeed, verticalError, verticalSpeed, U, V;
// //     Bottle * estimate=_inputEstimatePort.read(false);
// //     if(estimate!=NULL)
// //     {
// //         U=(estimate->get(4)).asDouble(); //PF coordinate U
// //         V=(estimate->get(5)).asDouble(); //PF coordinate V
// // 
// //       horizontalError=-320+U; //positive means the ball is on the right, in the image.
// //       verticalError=240-V; //positive means the ball is high, in the image.
// //       //printf("horizontalError: %f\n",horizontalError);
// //       horizontalSpeed=K*horizontalError;
// //       verticalSpeed=K*verticalError;
// //       int leftEye=0;
// //       int rightEye=1;
// //       int tilt=2;
// //       int pan=3;
// //       balta->move(leftEye, horizontalSpeed);
// //       balta->move(tilt, verticalSpeed);
// //     }

