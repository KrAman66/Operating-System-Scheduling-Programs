#include<iostream>
#include<algorithm>
using namespace std;

struct User
{
    int id;
    int burst_time;
};

bool compareUsers(User user1, User user2){
        return user1.burst_time<user2.burst_time;
    
}

int main(){
int n,i;
cout<<"Enter the number of User: ";
cin>>n;

User user[n];

for (i = 0; i < n; i++)
{
    cout<<"User"<<i+1<<endl;
    cout<<"ID:";
    cin>>user[i].id;
    cout<<"burst_time to be traveled: ";
    cin>>user[i].burst_time;


}
sort(user,user+n,compareUsers);
int waiting_time[n];
int turn_around_time[n];
waiting_time[0]=0;
for ( i = 1; i < n; i++)
{
    waiting_time[i]= user[i-1].burst_time+waiting_time[i-1];
}

for ( i = 0; i < n; i++)
{
    turn_around_time[i]= user[i].burst_time+waiting_time[i];
}

cout<<"User id\tBurstTime\tWaiting Time\tTurnaround Time\n"<<endl;
int t_waitingtime=0, t_turn_around_time=0;
for ( i = 0; i < n; i++)
{
    t_waitingtime+=waiting_time[i];
    t_turn_around_time+=turn_around_time[i];
    cout<< user[i].id<<"\t\t"<< user[i].burst_time<<"\t\t"<< waiting_time[i]<<"\t\t"<< turn_around_time[i]<< endl;
}
cout<<"Average time: "<<(float)t_waitingtime/(float)n<<endl;
float temp=(float)t_turn_around_time/n;
cout<<"Average Turnaround time: "<<temp<<endl;
cout<<"ThroughPut time: "<<(float)temp/n<<endl;
return 0;
}