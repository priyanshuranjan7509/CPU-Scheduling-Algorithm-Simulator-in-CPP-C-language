#include<bits/stdc++.h>

using namespace std;

typedef pair<unsigned int,unsigned int>pi;

#define size 20

class process_creator;

class scheduler;

 FILE *fp;

 FILE *fp2;

class process

{

    private:

      unsigned int process_id;

      unsigned int arrival_time;

      unsigned int burst_time;

      unsigned int turn_around_time;

      unsigned int waiting_time;

      unsigned int response_time;

      unsigned int completion_time;

      unsigned int starting_time;



      friend class process_creator;

      friend class scheduler;

    public:

    process(){

    arrival_time=-1;

    burst_time=-1;

    turn_around_time=-1;

    waiting_time=-1;

    response_time=-1;

    completion_time=-1;

    starting_time=-1;

    }

    void print(int i)

    {

    //fp = fopen("process.txt","a");

    fprintf(fp,"  %d        ", i);

    fprintf(fp,"%s    "," | ");

    fprintf(fp,"%d       ",arrival_time);

    fprintf(fp,"%s    "," | ");

    fprintf(fp,"%d       ",burst_time);

    fprintf(fp,"%s    "," | ");

    fprintf(fp,"%d       ",completion_time);

    fprintf(fp,"%s    "," | ");

     fprintf(fp,"%d      ",turn_around_time);

    fprintf(fp,"%s    "," | ");

     fprintf(fp,"%d      ",waiting_time);

    fprintf(fp,"%s    "," | ");

     fprintf(fp,"%d      ",response_time);

    fprintf(fp,"%s    "," | \n");

    

    }

};

class process_creator{

    friend class scheduler;

    friend class simulator;

    process p[size];

    public:

    void create_process()

    {

    for(int i=0;i<size;i++)

     p[i].process_id=i;

    srand(time(NULL));

    //int arival[]={69,149,276,308,373};

   // int burst[]={58,44,66,59,82};

    //rand()%count + starting sizeber

  /* generate secret sizeber between 1 and 100: */

    for(int i=0;i<size;i++)

       p[i].arrival_time=rand() % 50/*arival[i]*/;

       /* rand() % 10;*/ // generate sizebers

    for(int i=0;i<size;i++)

        p[i].burst_time=rand() % 50 +1 /*burst[i]*/;

        /*rand() % 20 +1;*/

        //return p;

     }  

    process fetch_process(int i){

      return p[i];

    }

};

class scheduler{

private:

  priority_queue<pi, vector<pi>, greater<pi>>ds;//this data structure gonna used for storing the processes 

  vector<int>Burst_Time;//will store burst time for every process

  queue<int>ready_queue;//this ready_queue will be used in FCFS and Round-Robin

  priority_queue<pi, vector<pi>, greater<pi>>ready_queue1;//this ready_queue will be used in SRTF

  int index,at;

  int running_process=-1;

  int completed=0;

  int start[size]={-1};

 int end[size]={-1};

  friend class simulator;

public:

 scheduler(){

   running_process=-1;

 };

 scheduler(string scheduler_name,process ps[])

  { 

    for(int i=0;i<size;i++)

      {

        ds.push({ps[i].arrival_time,ps[i].process_id});

        Burst_Time.push_back(ps[i].burst_time);

      }

        for(int i=0;i<size;i++)

       {

         ps[i].starting_time=-1;

       }

  }

  

//First Come First Serve algorithm

void FCFS_algo(process ps[],int i)

{

   while(!ds.empty()&& ds.top().first==i)//this condition is applied for first process p0

      {

         ready_queue.push(ds.top().second);//now process will be extracted from system and will be fitted in ready queue

               fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",ds.top().second);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Arrived ");

              fprintf(fp2,"%s  ","| \n");

              ds.pop();

      }

       if(running_process==-1&&!ready_queue.empty()){

            running_process=ready_queue.front();

            ready_queue.pop();//process will be extracted from ready queue and will be allocated to cpu

            }

       else if(running_process==-1&&ready_queue.empty()){

       }

       if(running_process!=-1&&Burst_Time[running_process]!=0)//process allocated to cpu is running

       {

             Burst_Time[running_process]-=1;

             fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

       }

      else if(running_process!=-1&&Burst_Time[running_process]==0)//one process has been finished and this condition checks the arrival time of new process 

      {

            ps[running_process].completion_time=i;

            ps[running_process].turn_around_time=ps[running_process].completion_time - ps[running_process].arrival_time;

            ps[running_process].waiting_time=ps[running_process].turn_around_time-ps[running_process].burst_time;

            ps[running_process].response_time=ps[running_process].waiting_time;

            fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Exited ");

              fprintf(fp2,"%s  ","| \n");

            if(ready_queue.empty())

            {

               running_process=-1;//cpu is idle at this time

            }

            else{

            running_process=ready_queue.front();

            ready_queue.pop();//process will be extracted from ready queue and will be allocated to cpu

            Burst_Time[running_process]-=1;//cpu will work upon process fetched from ready queue

            fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

            }

      }

}

//shortest remaining first time algorithm

void SRTF_algo(process ps[],int i){

 while(!ds.empty()&&i==ds.top().first)

         {

            ready_queue1.push({ps[ds.top().second].burst_time,ds.top().second});

             fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",ds.top().second);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Arrived ");

              fprintf(fp2,"%s  ","| \n");

            ds.pop();

         }

         if(running_process==-1&&ready_queue1.empty())

         {

         }

         else if(running_process==-1&&!ready_queue1.empty())

         {

              running_process=ready_queue1.top().second;

              ready_queue1.pop();

              //Burst_Time[running_process]-=1;

              if(ps[running_process].starting_time==-1)

                ps[running_process].starting_time=i;//this time means at this time for first time this process was allocated to cpu

               fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

          }

         if(running_process!=-1)

         {

            if(Burst_Time[running_process]==0)

            {

                

                //completed+=1;//one process has been completed

                ps[running_process].completion_time=i;

                ps[running_process].turn_around_time=ps[running_process].completion_time - ps[running_process].arrival_time;

                 ps[running_process].waiting_time=ps[running_process].turn_around_time-ps[running_process].burst_time;

                ps[running_process].response_time = ps[running_process].starting_time - ps[running_process].arrival_time;

              fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Exit ");

              fprintf(fp2,"%s  ","| \n");

               //now one process has been terminated ,so check for ready queue

               //if ready queue is empty

               if(ready_queue1.empty()){

                 running_process=-1;

                

               } 

               //if ready queue is not empty then we will extract process from ready queue and will be allocated to cpu

               else if(!ready_queue1.empty()){

              running_process=ready_queue1.top().second;

              ready_queue1.pop();

              Burst_Time[running_process]-=1;

               fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

              if(ps[running_process].starting_time==-1)

                 ps[running_process].starting_time=i;

               }

            }

            else if(Burst_Time[running_process]!=0)

            {

               //now we will check whether the ready queue is empty or not

               //if empty then just do Burst_Time[running_process]-=1

               //if not empty then compare the burst time of current ruuning process with burst time of arrived process in ready queue

               if(ready_queue1.empty()){

                Burst_Time[running_process]-=1;

                fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

               }

               else if(!ready_queue1.empty()){

                  if(Burst_Time[running_process]>ready_queue1.top().first)

                  {

                    //now this running process will be deallocated from cpu

                   fprintf(fp2,"%d  ", i);

                   fprintf(fp2,"%s  ","|  ");

                   fprintf(fp2,"%d  ", running_process);

                   fprintf(fp2,"%s  ","|  ");

                   fprintf(fp2,"%s  ","Exit ");

                   fprintf(fp2,"%s  ","| \n");

                    fprintf(fp2,"%d   ",i);

                    //the process that has been deallocated from cpu will be again added in Ready_Queue

                       fprintf(fp2,"%s  ","| ");

                       fprintf(fp2,"%d  ",running_process);

                       fprintf(fp2,"%s ","| ");

                       fprintf(fp2,"%s  ","Arrived ");

                      fprintf(fp2,"%s  ","| \n");

                       int running_process1=ready_queue1.top().second;

                       ready_queue1.pop();

                       ready_queue1.push({Burst_Time[running_process],running_process});

                      //now process will be extracted from ready queue and will be allocated to cpu

                       running_process=running_process1;

                       Burst_Time[running_process]-=1;

                       fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

                       if(ps[running_process].starting_time==-1)

                               ps[running_process].starting_time=i;

                  }

                  else if(Burst_Time[running_process]<=ready_queue1.top().first){

                    Burst_Time[running_process]-=1;

                    fprintf(fp2,"%d   ",i);

              fprintf(fp2,"%s  ","| ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","| ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

                  }

               }

            }

         }

}

//Round_Robin Algorithm

void RR_algo(process ps[],int i,int time_quanta){

 while(!ds.empty() && i==ds.top().first){

             ready_queue.push(ds.top().second);

             fprintf(fp2,"%d  ",i);

              fprintf(fp2,"%s  "," |  ");

              fprintf(fp2,"%d  ",ds.top().second);

             fprintf(fp2,"%s   ","|  ");

            fprintf(fp2,"%s    ","Arrived ");

            fprintf(fp2,"%s    ","| \n");

             ds.pop();

           }

         if(running_process==-1){

             if(ready_queue.empty()){

              

             }

             else if(!ready_queue.empty()){

              running_process=ready_queue.front();

              ready_queue.pop();

              if(ps[running_process].starting_time==-1)

                  ps[running_process].starting_time=i;

              start[running_process]=i;

              end[running_process]=start[running_process]+1;

              Burst_Time[running_process]-=1;

              fprintf(fp2,"%d  ",i);

              fprintf(fp2,"%s ","|  ");

              fprintf(fp2,"%d ",running_process);

             fprintf(fp2,"%s  ","|  ");

            fprintf(fp2,"%s   ","Running ");

            fprintf(fp2,"%s   ","| \n");

             }

           }

        else if(running_process!=-1){

             if(Burst_Time[running_process]==0){

                 ps[running_process].completion_time=i;

                 ps[running_process].turn_around_time=ps[running_process].completion_time - ps[running_process].arrival_time;

                 ps[running_process].response_time=ps[running_process].starting_time - ps[running_process].arrival_time;

                 ps[running_process].waiting_time=ps[running_process].turn_around_time-ps[running_process].burst_time;

              fprintf(fp2,"%d  ",i);

              fprintf(fp2,"%s  ","|  ");

              fprintf(fp2,"%d  ",running_process);

               fprintf(fp2,"%s ","|  ");

              fprintf(fp2,"%s  ","Exit ");

              fprintf(fp2,"%s  ","| \n");

                 //now its time to allocate new process iff present in ready queue to cpu

                 if(!ready_queue.empty())

                 {

              running_process=ready_queue.front();

              fprintf(fp2,"%d  ",i);

              fprintf(fp2,"%s  ","|  ");

              fprintf(fp2,"%d  ",running_process);

              fprintf(fp2,"%s  ","|  ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

                   ready_queue.pop();

                   Burst_Time[running_process]-=1;

                   if(ps[running_process].starting_time==-1)

                    {

                       ps[running_process].starting_time=i;

                    }

                    start[running_process]=i;

                    end[running_process]=start[running_process]+1;

                 }

                 else if(ready_queue.empty())

                 {

                   running_process=-1;

              

                 }

             }

              else if(Burst_Time[running_process]!=0&&end[running_process]-start[running_process]<time_quanta){

                Burst_Time[running_process]-=1;

                end[running_process]+=1;

              fprintf(fp2,"%d  ",i);

              fprintf(fp2,"%s  ","|  ");

              fprintf(fp2,"%d  ",running_process);

              fprintf(fp2,"%s  ","|  ");

              fprintf(fp2,"%s  ","Running ");

              fprintf(fp2,"%s  ","| \n");

             }

             else if(Burst_Time[running_process]!=0 && end[running_process]-start[running_process]==time_quanta){

               if(!ready_queue.empty()){

                  fprintf(fp2,"%d  ", i);

                   fprintf(fp2,"%s  ","|  ");

                   fprintf(fp2,"%d  ", running_process);

                   fprintf(fp2,"%s  ","|  ");

                   fprintf(fp2,"%s  ","Exit ");

                   fprintf(fp2,"%s  ","| \n");

                   ready_queue.push(running_process);

                   start[running_process]=-1;

                   end[running_process]=-1;

                   running_process=ready_queue.front();

                   fprintf(fp2,"%d  ", i);

                   fprintf(fp2,"%s  ","|  ");

                   fprintf(fp2,"%d  ", running_process);

                   fprintf(fp2,"%s  ","|  ");

                   fprintf(fp2,"%s  ","Running ");

                   fprintf(fp2,"%s  ","| \n");

                    ready_queue.pop();

                    Burst_Time[running_process]-=1;

                    if(ps[running_process].starting_time==-1)

                    {

                       ps[running_process].starting_time=i;

                    }

                    start[running_process]=i;

                    end[running_process]=start[running_process]+1;

               }

               else if(ready_queue.empty()){

                   Burst_Time[running_process]-=1;

                   start[running_process]=i;

                   end[running_process]=start[running_process]+1;

                   fprintf(fp2,"%d  ",i);

                   fprintf(fp2,"%s","|  ");

                    fprintf(fp2,"%d",running_process);

                   fprintf(fp2,"%s","|  ");

                    fprintf(fp2,"%s","Running ");

                     fprintf(fp2,"%s","| \n");

               }

            }

        }   

}

};

class simulator{

    private:

    int simulator_time=1;//in terms of second

    public:

    simulator(string scheduling_algo,int val)

    {

      //setting time quantum

      simulator_time=val;

      process p[size];

      process_creator obj;

      obj.create_process();

      for(int j=0;j<size;j++){

        p[j]=obj.fetch_process(j);

      }

     if(scheduling_algo=="FCFS"){

    // scheduler scheduler1;

    cout << "welcome to FCFS " << endl;

    scheduler  scheduler1(scheduling_algo,p);

     for(int t=0;t<simulator_time*1000;t++){

       scheduler1.FCFS_algo(p,t);

     }

     }

     else if(scheduling_algo=="SRTF"){

       cout << "welcome to SRTF " << endl;

       scheduler scheduler2(scheduling_algo,p);

     for(int t=0;t<simulator_time*1000;t++){

        scheduler2.SRTF_algo(p,t);

     }

     }
     for(int i=0;i<size;i++){

       p[i].print(i);

     }

    }

    simulator(string scheduling_algo,int time_quanta,int val){

       //setting time quantum

      simulator_time=val;

      process p[size];

      process_creator obj;

      obj.create_process();

      for(int j=0;j<size;j++){

        p[j]= obj.fetch_process(j);
        cout << "process" << endl;

      }

     scheduler scheduler3(scheduling_algo,p);

     for(int t=0;t<simulator_time*1000;t++){

        scheduler3.RR_algo(p,t,time_quanta);

     }
     for(int i=0;i<size;i++){

       p[i].print(i);

     }

    }

};

int main()

{

    //writing into process.txt file

    fp = fopen("process.txt","w");

    fprintf(fp,"%s","Process Id ");

    fprintf(fp,"%s","| ");

    fprintf(fp,"%s","Arrival Time ");

    fprintf(fp,"%s","| ");

    fprintf(fp,"%s","Burst Time ");

    fprintf(fp,"%s","| ");

    fprintf(fp,"%s","Completion Time ");

    fprintf(fp,"%s","| ");

     fprintf(fp,"%s","Turn Around Time ");

    fprintf(fp,"%s","| ");

     fprintf(fp,"%s","Waiting Time ");

    fprintf(fp,"%s","| ");

     fprintf(fp,"%s","Response Time ");

    fprintf(fp,"%s","| \n");

   //writing into status.txt file 

    fp2=fopen("status.txt","w");

    fprintf(fp2,"%s","Milli_scnd");

    fprintf(fp2,"%s","| ");

    fprintf(fp2,"%s","P_Id ");

    fprintf(fp2,"%s","| ");

    fprintf(fp2,"%s","Status ");

    fprintf(fp2,"%s","| \n");

     cout << "Enter process scheduling algorithm of your choice::" << endl;

     cout << "For FCFS enter 1 "<< endl;

     cout <<"For SRTF enter 2 "<< endl;

     cout << "for RR enter 3 " << endl;

    int scheduling_algorithm;

     cin >> scheduling_algorithm;

     int simulation_time;

     cout <<"Please Enter Simulation Time::" << endl;

     cin >> simulation_time;

     if(scheduling_algorithm==1){

        simulator s("FCFS",simulation_time);

     }

     else if(scheduling_algorithm==2){

     simulator s("SRTF",simulation_time);

     }

     else if(scheduling_algorithm==3){

     int Time_Quantum;

      cout << "please enter time quantum for round robin algorithm::\n";

     cin >> Time_Quantum;

      simulator("RR",Time_Quantum,simulation_time);

     }



    fclose(fp);

    fclose(fp2);

    return 0; 

}
