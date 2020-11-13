#define BLACK 0 
#define WHITE 15 

#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<random>
#include<WinInet.h>
#include<conio.h>
#pragma comment (lib, "WinInet.lib")
#define thin_bar "------------------------------------------\n";
#define small_bar "=====================\n";
#define long_bar "==========================================\n";
#define SIZE words.size()
#define UNBAR char(95)
#define cons name<<") "
#define InitSc  cout << "  ------\n  |    |\n  |    \n  |   \n----  \n"
using namespace std;

class Hangman {
private:
    string name;
    string wrong;
    string pw;
    string words;
    string wordsarr[853];
    char answer;
    string PwS[100]{""};
    string NameS[100]{""};
    int ScoreS[100]{ 0 };
    int life;
    int fe;
    int pcount = 0;
    int index;
    int wrongcount;
    bool isright;
    int score;
    int t1;
    char underbar[100]{};
    int count;
public:
    Hangman() {
        Rank();
    }

    Hangman(string n) {
        score = 100;
        readwords();
        wrongcount = 0;
        isright = true;
        pcount = 0;
        FileReader();
        name = n;
        life = 6;
        
       
       // gamestart();
    }
    void newplayer() {
        if (IsNew()) {
            string p;
            string p2;
            cout << "비밀번호를 입력해주세요\n";
            cin >> p;
            cout << "한번 더 입력해주세요\n";
            cin >> p2;
            while (p != p2) {
                cout << "첫 비밀번호와 다릅니다. 다시 입력해주세요." << endl;
                cin >> p2;
            }
            pw = p2;
            count++;
            PwS[fe] = pw;
            NameS[fe] = name; //수정필요!!!!
            ScoreS[fe] = score;
            gamestart();
        }
        else {
            cout << "당신은 새로운 플레이어가 아닙니다. 메인 메뉴로 이동합니다." << endl;
            Sleep(2000);
            return;
        }
    }
    void continueplaying() {
        if (Isthere()) {
            string s;
            cout << "비밀번호를 입력해주세요\n";
            cin >> s;
            while (pw != s) {
                cout << "비밀번호가 틀렸습니다. 다시 입력해주세요.(나가기 : exit입력)\n";
                cin >> s;
                if (s == "exit") return;
            }
            gamestart();
        }
        else {
            cout << "당신은 새로운 플레이어입니다. 메인 메뉴로 이동합니다." << endl;
            Sleep(1000);
            return;
        }
    }

    bool IsNew() {
        for (int i = 0; i < 100; i++)
        {
            if (NameS[i] == name) {
                return false;
            }
        }
        return true;
    }

    bool Isthere() {
        for (int i = 0; i < 100; i++)
        {
            if (NameS[i] == name) {
                score = ScoreS[i];
                pw = PwS[i];
                return true;
            }
        }
        return false;

    }
   

    void aftergame() {//
        for (int i = 0; i <= fe; i++)
        {
            if (NameS[i] == name) {
                ScoreS[i] = score;
                PwS[i] = pw;
            }
        }
        cout << "File download start\n";
        FileDownload();
        Sleep(1000);
        cout << "downloading.";
        Sleep(500);
        cout << ".";
        Sleep(500);
        cout << ".\n";
        Sleep(1000);
        cout << "File download complete\n";
        FileEditor();
        cout << "File update start\n";
        Sleep(3000);
        FileUpload();
        cout << "File update complete\n";
        Sleep(2000);
    }
    void fileupdatewithoutmsg() {
        for (int i = 0; i <= fe; i++)
        {
            if (NameS[i] == name) {
                ScoreS[i] = score;
                PwS[i] = pw;
            }
        }
        FileDownload();
        Sleep(2000);
        FileEditor();
        Sleep(1000);
        FileUpload();
    }
    void FileReader() {
        fe = 0;
        ifstream in;
        in.open("score.dll", ios::binary); //사실 binary로 저장이 안됨;
        in >> count;
        while (fe < count) { //score.dll에는 사람명수, (이름, 비번, 점수) (이름, 비번, 점수) ...로 들어있음
            in >> NameS[fe] >> PwS[fe] >> ScoreS[fe]; //이름,비번,점수를 읽어서 멤버 변수에 배열 형태로 저장
            fe++;
        }
    }

    void FileEditor() { //새로 작성
        ofstream out;
        out.open("score.dll", ios::binary);
        out << count << " ";
        for (int i = 0; i <= fe; i++) {
            out << NameS[i] << " " << PwS[i] << " " << ScoreS[i] << " "; //게임을 하고, 추가된 정보까지 포함해 멤버 변수에 저장된 모든 정보를 다시 새로 score.dll에 작성
        }
    }

    void FileDownload() {
        WinExec("FILE\\decrease.exe", SW_SHOW); //WinExec는 외부 프로그램을 실행해줌
    }

    void FileUpload() {
        WinExec("FILE\\increase.exe", SW_SHOW);
    }

    void readwords() {
        ifstream file;
        file.open("chicken.dll");
        if (!file.is_open()) {
            cout << "단어장이 없습니다! 파일을 다시 다운로드하세요\n";
            exit(1);
        }
        for (int i = 0; i < 851; i++) {
            file >> wordsarr[i];
        }
    }
    void randing() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, 852);
        t1 = dis(gen);
        words = wordsarr[t1];
    }
    void image(int a) { 
        if (a == 1) {
            cout << "  ------\n";
            cout << "  |    |\n";
            cout << "  |    O\n";
            cout << "  |   /|＼\n";
            cout << "----  / \n";
        }
        else if (a == 0) {
            cout << "  ------\n";
            cout << "  |    |\n";
            cout << "  |    O\n";
            cout << "  |   /|＼\n";
            cout << "----  / ＼\n";
        }
        else if (a == 5) {
            cout << "  ------\n";
            cout << "  |    |\n";
            cout << "  |    O\n";
            cout << "  |   \n";
            cout << "----  \n";
        }
        else if (a == 4) {
            cout << "  ------\n";
            cout << "  |    |\n";
            cout << "  |    O\n";
            cout << "  |    |\n";
            cout << "----  \n";
        }
        else if (a == 3) {
            cout << "  ------\n";
            cout << "  |    |\n";
            cout << "  |    O\n";
            cout << "  |   /|\n";
            cout << "----  \n";
        }
        else if (a == 2) {
            cout << "  ------\n";
            cout << "  |    |\n";
            cout << "  |    O\n";
            cout << "  |   /|＼\n";
            cout << "----  \n";
        }
        else if (a == 1) {
            cout << "  ------\n";
            cout << "  |    |\n";
            cout << "  |    O\n";
            cout << "  |   /|＼\n";
            cout << "----  / \n";
        }
        else if (a == 6) {
            InitSc;
        }
        else if (a == -1) {
            cout << "  ------\n";
            cout << "  |    |\n";
            cout << "  |    O\n";
            cout << "  |       \n";
            cout << "  |       \n";
            cout << "  |   /|＼\n";
            cout << "----  / ＼\n";
        }
        for (int i = 0; i < SIZE; i++)
        {
            cout << underbar[i] << " ";
        }
    }
   
    void Rank() {
        int temp;
        string temp2;
        FileReader();


        for (int i = 0; i < fe; i++)
        {
            for (int j = 0; j < fe - 1 - i; j++) { //얘는 rank를 출력할때 큰거부터 출력해야 하니까 그걸 위해서 버블정렬
                if (ScoreS[j] < ScoreS[j + 1]) {
                    temp = ScoreS[j];
                    temp2 = NameS[j];
                    ScoreS[j] = ScoreS[j + 1];
                    NameS[j] = NameS[j + 1];
                    ScoreS[j + 1] = temp;
                    NameS[j + 1] = temp2;
                }
            }
        }
        for (int i = 0; i < fe; i++)
        {
            if (NameS[i].compare("")) { //가끔 파일을 저장하는 과정에서 불필요한 ""가 저장되고 이를 이름으로 받아드리는 경우가 있는데, 그 경우를 제외하고 출력
                cout << i + 1 << " " << NameS[i] << " " << ScoreS[i] << endl;
            }
        }
    }
    bool isGameEnd() {
        for (int i = 0; i < SIZE; i++)
        {
            if (underbar[i]==UNBAR) {
                return false;
            }
        }
        return true;
    }
    void blank(char ans) {
       // system("cls");
        isright = false;
        for (int i = 0; i < SIZE; i++)
        {
            if (words[i] == ans) {
                underbar[i] = ans;
                isright = true;
            }
        }
        if (!isright) {
            life--;
        }
        
        cout << endl;
    }
    void initialize() {
        wrongcount = 0;
        isright = false;
        life = 6;
        for (int i = 0; i < SIZE; i++)
        {
            underbar[i] = {};
            wrong = "";
        }
    }
    void calscore() {
        if (wrongcount == 0) {
            cout << "\n한번에 맞추셨네요!\n";
            score = score + 2000;
        }
        else if (wrongcount < 7) {
            score = score + (100 * SIZE) - (10 * wrongcount);
        }
        else score = score - 10 * SIZE;
    }
    void gamestart() {
        initialize();
       
        cout << "당신의 현재 점수는 " << score << "점 입니다." << endl;
        randing();
        for (int i = 0; i < SIZE; i++)
        {
            strcat_s(underbar, "_");
        }
        InitSc;
        for (int i = 0; i < SIZE; i++)
        {
            cout << underbar[i] << " ";
        }cout << endl;
        cout << "\n틀린 글자 : " << wrong << endl;
       
        while (!isGameEnd()) {
            cout << "\n\n알파벳(소문자)을 입력해주세요\n";
            cout << cons;
            cin >> answer;
            while (answer < 97 || answer>122) {
                cout << "잘못 입력했습니다.. 다시 입력해 주세요\n";
                cout << cons;
                cin >> answer;
            }
            system("cls");
            blank(answer);
            image(life);
            cout << "\n\n";
            if (!isright) {
                wrong = wrong+answer+" ";
                wrongcount++;
            }
            cout << "틀린 글자 : " << wrong << " 틀린 횟수 : " << wrongcount << endl;
            if (wrongcount == 7) {
                system("cls");
                image(-1);
                cout << "\n\n틀린 글자 : " << wrong << " 틀린 횟수 : " << wrongcount << endl;
                cout << "\n패배하셨습니다!\n정답 : " << words;
                break;
            }
        }
        calscore();
        if (wrongcount < 7) {
            cout << "정답입니다! 점수 : " << score << endl;
        }
        else cout << "\n점수 : " << score;
        fileupdatewithoutmsg();
        cout << "\n\n더 하시겠습니까? 1. 네 2. 아니오"<<endl;
        int m;
        cout << cons;
        cin >> m;
        while (!(m==1||m==2)) {
            cout << "잘못 입력했습니다. 다시 입력해주세요. " << endl;
            cout << cons;
            cin >> m;
        }
        system("cls");
        if (m == 1) gamestart();
        else aftergame();
    }
};
void textcolor(int, int);
void option() { //옵션 모드
    system("cls");
    while (true) {
        cout << "1. 야간 모드\n";
        cout << "2. 야간 모드 해제\n";
        cout << "3. 만든 사람 신상 캐기\n";
        cout << "4. 옵션 끝내기\n";
        int num;
        cout << "You) ";
        cin >> num;
        while (!(num == 1 || num == 2 || num == 3 || num == 4)) {
            cout << "잘못 입력하셨습니다. 다시 입력해주세요.\n";
            cout << "You) ";
            cin >> num;
        }
        if (num == 1) {
            textcolor(WHITE, BLACK); //콘솔창 색깔 변경
            system("cls");
        }
        else if (num == 2) {
            textcolor(BLACK, WHITE);
            system("cls");
        }
        else if (num == 3) {
            system("cls");
            cout << "인하대학교 컴퓨터동아리 인컴 40기 교육/학술부장 박경대 및 40기 일동 제작\n\n";
        }
        else if (num == 4) {
            break;
        }
    }
}
void textcolor(int foreground, int background)
{
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); //콘솔 배경과 콘솔 글씨 색을 변경해주는 windows.h에 있는 함수 사용
}
void Screen();
void whatsyourname() { //이름이 뭐냐고 묻고, 게임 클래스에 이름을 매개하여 넘겨줌
    int num2;
    cin >> num2;
    string name;
    while (!(num2 == 1 || num2 == 2)) {
        cout << "잘못 입력하셨습니다. 다시 입력해주세요.\n";
        cout << "You) ";
        cin >> num2;
    }
    if (num2 == 1) {
        cout << "이름이 무엇입니까? \n";
        cout << "You) ";
        cin >> name;
        Hangman G(name);
        cout << thin_bar;
        G.newplayer(); //새로운게임시작
        Screen();
    }
    else if (num2 == 2) {
        cout << "이름이 무엇입니까? \n";
        cout << "You) ";
        cin >> name;
        cout << thin_bar;
        Hangman G(name);
        G.continueplaying(); //계속하기 시작
        Screen();
    }
}
void Screen() {
    system("cls"); //콘솔 창 비우기
    cout << "////V 1.0.1 Hangman Game////\n(C)Incom 40th.\n";
    WinExec("FILE\\decrease.exe", SW_HIDE);
    cout << small_bar;
    cout << "1. 게임 시작\n";
    cout << "2. 온라인 순위 보기\n";
    cout << "3. 게임 방법 보기\n";
    cout << "4. 순위 갱신하기\n";
    cout << "5. 옵션 보기\n";
    cout << "6. 비밀번호 변경/계정 탈퇴\n";
    cout << "7. 끝내기\n";
    cout << small_bar;
    string name;
    cout << "You) ";
    int num;

    cin >> num;
    while (!(num == 1 || num == 2 || num == 3 || num == 4 || num == 5 || num == 6 || num == 7)) {
        cout << "잘못 입력하셨습니다. 다시 입력해주세요.\n";
        cout << "You) ";
        cin >> num;
    }
    if (num == 1) {
        system("cls");
        cout << "1. 새로운 플레이어\n";
        cout << "2. 계속하기\n";
        cout << "You) ";
        whatsyourname();
    }
    else if (num == 2) {
        system("cls");
        Hangman G1;
        cout << "\n메인 화면으로 이동하려면 엔터 키를 눌러주세요.\n" << endl;
        int key;
        while (true) {
            if (_kbhit()) { //키 입력 대기
                key = _getch(); //엔터키가 들어오면 메인화면(InitialScreen)으로 이동
                if (key == 13) {
                    system("cls");
                    Screen();
                    return;
                }
            }
        }
    }
    else if (num == 3) {
        system("cls");
        cout << long_bar;
        cout << " 알파벳을 입력하여 영어 단어를 맞추는 게임입니다. 기회는 6번!\n\n ##점수계산##\n\n 정답 : 알파벳 하나당 100점 UP, 틀린 갯수당 10점 DOWN\n 오답 : ";
        cout << "알파벳 하나당 10점 DOWN \n 한번에 맞추면 2000점 UP!\n";
        cout << long_bar;
        cout << "\n메인 화면으로 이동하려면 엔터 키를 눌러주세요." << endl;
        int key;
        while (true) {
            if (_kbhit()) {
                key = _getch();
                if (key == 13) {
                    system("cls");
                    Screen();
                    return;
                }
            }
        }
    }
    else if (num == 4) {
        WinExec("FILE\\decrease.exe", SW_SHOW);
        cout << "File Updating..." << endl;
        Sleep(3000);
        cout << "File Updated!";
        Sleep(1500);
        Screen();
    }
    else if (num == 5) {
        option();
        Screen();
    }
    else if (num == 6) {
        cout << "비밀번호 변경/ 계정 삭제는 경대에게 문의하세요\n";
        Sleep(3000);
        Screen();
    }
    else return;
}
void ScreenPrint() { //시작하기 전에 인터넷 연결 여부 확인
    DWORD dwFlag;
    TCHAR szName[256];
    BOOL bInternet = ::InternetGetConnectedStateEx(&dwFlag, szName, 256, 0); //인터넷 연결 확인 함수
    for (int i = 0; i < 3; i++)
    {
        cout << "인터넷 연결 확인중.";
        Sleep(200);
        system("cls");
        cout << "인터넷 연결 확인중..";
        Sleep(200);
        system("cls");
        cout << "인터넷 연결 확인중...";
        Sleep(200);
        system("cls");
    }
    if (bInternet) //인터넷이 연결되어 있으면
    {
        printf("인터넷 연결 확인!\n");
        Sleep(1500);
        WinExec("FILE\\decrease.exe", SW_SHOW);
        for (int i = 0; i < 3; i++)
        {
            cout << "Downloading.";
            Sleep(200);
            system("cls");
            cout << "Downloading..";
            Sleep(200);
            system("cls");
            cout << "Downloading...";
            Sleep(200);
            system("cls");
        }
        cout << "HANGMAN GAME\n";
        Sleep(500);
        cout << "현재 버전은 1.0.1 입니다. 최신 버전입니다." << endl;
        Sleep(1000);
        system("cls");
    }
    else {
        cout << "인터넷이 연결되어 있지 않습니다.\n게임을 종료합니다.\n";
        exit(1);
    }
}
bool isFolder() { //사용자 이름 폴더에 .aws가 들어가 있는가를 알려주는 함수
    char szUserName[MAX_PATH] = { 0 };
    DWORD dwLength = MAX_PATH;
    GetUserName(szUserName, &dwLength);
    string username(szUserName);
    string s = "C:\\Users\\" + username + "\\.aws";
    wstring dir = wstring(s.begin(), s.end());
    const wchar_t* dir_result = dir.c_str(); //string ->wstring->wchar_t*
    //여기까지 대충 폴더 경로 지정(string ->wchar_t* 형태로 변환)
    int rst = 0;
    rst = _waccess_s(dir_result, 0);
    if (rst == 0) { //폴더가 있으면 true 없으면 false
        return true;
    }
    else return false;
}
int main() {
    SetConsoleTitle("Hangman V 1.0.1"); //콘솔 제목 변경

    for (int i = 0; i < 2; i++)
    {
        cout << "Hangman 구동 중.";
        Sleep(200);
        system("cls");
        cout << "Hangman 구동 중..";
        Sleep(200);
        system("cls");
        cout << "Hangman 구동 중...";
        Sleep(200);
    }
    cout << "\n\n";
    Sleep(500);
    if (isFolder()) { //.aws폴더가 사용자 이름 폴더에 잘 있으면
        cout << ".aws 폴더 확인 완료.\n\n";
        Sleep(1000);
        //system("cls");
    }
    else {
        cout << ".aws 폴더가 없습니다.\n\nInstaller를 실행합니다.\n\n잠시만 기다려주세요.\n\n";
        WinExec(".\\inst.exe", SW_SHOW);
        Sleep(5000);
    }

    textcolor(WHITE, BLACK); //기본 : 검은 배경에 하얀 글씨
    ScreenPrint(); //+ Internet check, download
    Screen();
}
