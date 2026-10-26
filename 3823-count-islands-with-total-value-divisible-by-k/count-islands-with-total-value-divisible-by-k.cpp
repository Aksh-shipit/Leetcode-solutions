class Solution {
public:
int m,n;
  long long bfs(vector<vector<int>>& grid,int i,int j){
    queue<pair<int,int>> q;

    q.push({i,j});

    long long sum=grid[i][j];

    grid[i][j]=0;

    int dr[]={1,-1,0,0};
    int dc[]={0,0,1,-1};

    while(!q.empty()){
        int r=q.front().first;
        int c=q.front().second;

        q.pop();

        for(int d=0;d<4;d++){
            int nr=r+dr[d];
            int nc=c+dc[d];

            if(nr>=0 && nr<m && nc>=0 && nc<n && grid[nr][nc]>0){
                sum+=grid[nr][nc];

                grid[nr][nc]=0;

                q.push({nr,nc});
            }
        }
    }

    return sum;

  }
    int countIslands(vector<vector<int>>& grid, int k) {
        m=grid.size();
        n=grid[0].size();
        int ans=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]>0){
                    long long islandSum=bfs(grid,i,j);

                    if(islandSum%k==0){
                        ans++;
                    }
                }
            }
        }
        return ans;
        
    }
};