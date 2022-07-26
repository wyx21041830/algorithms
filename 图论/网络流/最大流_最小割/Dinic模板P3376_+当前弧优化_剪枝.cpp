#include <bits/stdc++.h>
#define LOCAL
using namespace std;
//#define int long longA
// dinic
int T;
const int inf = 0x3f3f3f3f;
const int MAXN = 20005;   // DIAN
const int MAXM = 500005;  // BIAN
int n, m, s, t, u, v;     //注意这些变量含义 
int tot;                //杈瑰簭鍙蜂粠2寮�濮�  (0~1),  2~3  4~5
int w, ans, dep[MAXN];  //鐐圭殑灞傛繁搴�
int head[MAXN];         //閾惧紡鍓嶅悜鏄�  鐐筰瀵瑰簲璧峰杈�
int cur[MAXN];          //褰撳墠寮т紭鍖�
//瀵逛簬涓�涓妭鐐箈x锛屽綋瀹冨湪DFS涓蛋鍒颁簡绗琲i鏉″姬鏃讹紝鍓峣-1鏉″姬鍒版眹鐐圭殑娴佷竴瀹氬凡缁忚娴佹弧鑰屾病鏈夊彲琛岀殑璺嚎浜�
//閭ｄ箞褰撲笅涓�娆″啀璁块棶xx鑺傜偣鏃讹紝鍓峣-1鏉″姬灏辨病鏈変换浣曟剰涔変簡
//鎵�浠ユ垜浠彲浠ュ湪姣忔鏋氫妇鑺傜偣x鎵�杩炵殑寮ф椂锛屾敼鍙樻灇涓剧殑璧风偣锛岃繖鏍峰氨鍙互鍒犻櫎璧风偣浠ュ墠鐨勬墍鏈夊姬锛屾潵杈惧埌浼樺寲鍓灊鐨勬晥鏋�
//瀵瑰簲鍒颁唬鐮佷腑锛屽氨鏄痗ur鏁扮粍
struct EDGE {
  int to, next;
  int flow;         //鍓╀綑娴侀噺
} edge[MAXM << 1];  //鍙嶅悜杈瑰弻鍊�

void add(int u, int v, int w) {  //鍚屾椂鍔犳鍙嶄袱鏉¤竟
  edge[++tot].to = v;
  edge[tot].flow = w;
  edge[tot].next = head[u];
  head[u] = tot;

  edge[++tot].to = u;
  edge[tot].flow = 0;  //鍙嶅悜寮у垵濮嬪寲涓�0
  edge[tot].next = head[v];
  head[v] = tot;
}

int bfs(int s, int t) {  // bfs  鍦ㄦ畫閲忕綉缁滀腑鏋勯�犲垎灞傚浘
  for (int i = 0; i <= n; i++)
    dep[i] = inf, cur[i] = head[i];  // dep鍒濆鍖栨棤绌� 鍚屾椂璧锋爣璁颁綔鐢�
  queue<int> que;  //  cur 鍒濆鍖栦负head   鐢ㄤ簬涔嬪悗寮т紭鍖�
  que.push(s);
  dep[s] = 0;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (int i = head[u]; ~i; i = edge[i].next) {  //閬嶅巻杈�
      if (edge[i].flow == 0) continue;             //鏃犲墿浣欐祦閲忚烦杩�
      int v = edge[i].to;
      if (edge[i].flow>0 && dep[v] == inf) {  // 鏈夋畫浣欐祦閲忎笖涓鸿闂�
        que.push(v);
        dep[v] = dep[u] + 1;   //璁板綍娣卞害
        if (v == t) return 1;  //璺冲嚭  鎵惧埌涓�鏉″骞胯矾
      }
    }
  }
  return 0;
}
// 鍦ㄥ眰娆″浘鍩虹涓婁笉鏂璬fs 姹傚緱澧炲箍璺� (澶氭潯)
int dfs(int u, int sum) {  // sum琛ㄧず褰撳墠娴佸叆鍙鐐圭殑鍓╀綑娴侀噺
  if (u == t) return sum;
  int k, res = 0;  // k涓哄綋鍓嶆渶灏忓墿浣欏閲�
  for (int i = cur[u]; (~i )&& sum; i = edge[i].next) {  // 寮т紭鍖�  sum
    cur[u] = i; //褰撳墠寮т紭鍖�                                       //寮т紭鍖�
    int v = edge[i].to;
    if (edge[i].flow > 0 && (dep[v] == dep[u] + 1)) {  //鏈夊墿浣欐祦閲�  灞傛暟宸�1
      k = dfs(v, min(sum, edge[i].flow));              //  u娴佸叆v鐨勬祦閲�
      if (k == 0) dep[v] = inf;  //*鍓灊锛� 鍘绘帀澧炲箍瀹岀殑鐐�
      edge[i].flow -= k;
      edge[i ^ 1].flow += k;
      res += k;  // res琛ㄧず缁忚繃璇ョ偣鐨勬墍鏈夋祦閲忓拰锛堢浉褰撲簬娴佸嚭鐨勬�婚噺锛�
      sum -= k;  // sum琛ㄧず缁忚繃璇ョ偣鐨勫墿浣欐祦閲� (鏈夊涓獀)
    }
  }
  return res;
}

signed main() {

#ifdef LOCAL
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
#endif

  memset(head, -1, sizeof head);
  memset(edge, 0, sizeof edge);
 tot=1;
ans=0;
cin>>n>>m>>s>>t;
for(int i=1;i<=m;i++){
  cin>>u>>v>>w;
  add(u,v,w);
}


while(bfs(s,t)){
  ans+=dfs(s,inf);
}
cout<<ans<<endl;
  return 0;
}
