#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int solve(vector<int>& days,vector<int>& costs,int index) {
    if(index>=days.size())
        return 0;
//One day pass
    int option1 = costs[0]+solve(days,costs,index+1);

//seven days pass
    int i;
    for(i = index; i<days.size() && days[i]<days[index]+7; i++);

    int option2 = costs[1]+solve(days,costs,i);

//Thirty days pass
    for(i=index; i<days.size() && days[i]<days[index]+30; i++);

    int option3 = costs[2]+solve(days,costs,i);

    return min(option1,min(option2,option3));

}
//dp sol
int memo(vector<int>& days,vector<int>& costs,int index,vector<int>dp) {
    if(index>=days.size())
        return 0;
    if(dp[index]!= -1)
        return dp[index];
//One day pass
    int option1 = costs[0]+memo(days,costs,index+1,dp);

//seven days pass
    int i;
    for(i = index; i<days.size() && days[i]<days[index]+7; i++);

    int option2 = costs[1]+memo(days,costs,i,dp);

//Thirty days pass
    for(i=index; i<days.size() && days[i]<days[index]+30; i++);

    int option3 = costs[2]+memo(days,costs,i,dp);

    dp[index] = min(option1,min(option2,option3));
    return dp[index];
}
// Solve tabular
int tab(vector<int>& days,vector<int>& costs) {
    int n = days.size();
    vector<int>dp(n+1,0);
    dp[n] = 0;
    for(int k = n-1; k>=0; k--) {
//One day pass
        int option1 = costs[0]+dp[k+1];

//seven days pass
        int i;
        for(i = k; i<days.size() && days[i]<days[k]+7; i++);

        int option2 = costs[1]+dp[i];

//Thirty days pass
        for(i=k; i<days.size() && days[i]<days[k]+30; i++);

        int option3 = costs[2]+dp[i];

        dp[k] = min(option1,min(option2,option3));

    }
    return dp[0];
}
int optimisation(vector<int> & days,vector<int>& cost) {
int ans = 0;
queue<pair<int,int>>month;
queue<pair<int,int>>week;


for(int day : days){
//remove expire day
while(!month.empty() && month.front().first + 30<=day)
    month.pop();
while(!week.empty() && week.front().first + 7<=day)
    week.pop();
//add cost of current day
week.push(make_pair(day,ans+cost[1]));
month.push(make_pair(day,ans+cost[2]));
//update ans
ans = min(ans+cost[0],min(week.front().second,month.front().second));

}
return ans;
}
int main()
{
    vector<int>days;
    days.push_back(1);
    days.push_back(4);
    days.push_back(6);
    days.push_back(7);
    days.push_back(8);
    days.push_back(20);
    vector<int>cost;
    cost.push_back(2);
    cost.push_back(7);
    cost.push_back(15);
    vector<int>dp(days.size(),-1);
    cout<<"Rec ans is -> "<<solve(days,cost,0)<<endl;
    cout<<"Memoization ans is -> "<<memo(days,cost,0,dp)<<endl;
    cout<<"Tabular ans is -> "<<tab(days,cost)<<endl;
    cout<<"minimize ans is -> "<<optimisation(days,cost)<<endl;
    return 0;
}
