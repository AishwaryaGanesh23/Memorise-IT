#define SIZE 3

void display_file(char filename[10]);
void game_menu();
void init_num_mat(char num[SIZE][SIZE]);
void init_star_mat(char star[SIZE][SIZE]);
int game_play(char uname[10],char star[SIZE][SIZE],char num[SIZE][SIZE]);
void gametime();
void display_matrix(char star[SIZE][SIZE]);
int check_random(int random,char num[SIZE][SIZE]);
int check_numbers(char num[SIZE][SIZE]);
void enter_to_continue( FILE *in);
void score_store(char uname[10],int score);




