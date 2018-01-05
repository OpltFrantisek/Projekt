class Key{
    int  * row;
    int  * col;
    char keyMap[4][4] = {{'1','2','3','A'},
                         {'4','5','6','B'},
                         {'7','8','9','C'},
                         {'*','0','#','D'}};
public:
    void Init(int  r[],int  c[],int rl,int sl);
    char stiskTl();

};
