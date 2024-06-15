//source libraries from file
#include "headers.h"

int graphColor(bool write){
  FILE *colorFile;
  int out;
  colorFile = fopen("color.txt","r");
  char colorChar[5];
  if(fgets(colorChar,5,colorFile)==NULL){puts("Fgets error");}
  int setColor[3] = {95,94,31};
  sscanf(colorChar,"%d",&out);
  fclose(colorFile);
  if(write){
    colorFile = fopen("color.txt","w");
    out++;
    if(out>2){
      out=0;
    }
    fprintf(colorFile,"%d",out);
    fclose(colorFile);
    return 0;
  }
  return setColor[out];
}


//Graphics Matrix
//Semantic function parser -- (maybe not)
//recursive allocation for matrix and memory
//user friendly menu

//SHELL RUN COMMAND: gcc -o main main.c -lm  && ./main

//function to deduce print position in array: halfRes +- ((n*10)/2)

//if-else nests disguised as a 'dynamic renderer'
void menu();
void list_init(char enteredFrom);
int main(void);
//Input error handling - while copied straight from stackoverflow
double validInput(char flavor[]){
  int c;
  double x;
  while (scanf("%lf", &x) != 1) {
    while (!isspace(c = getchar()));
    ungetc(c, stdin);
    (strcmp(flavor,""))? printf(ANSI_COLOR_RED "You must enter a valid number. Try again.\n" ANSI_COLOR_RESET) : printf("%s",flavor);
    printf(ANSI_COLOR_YELLOW "\n> " ANSI_COLOR_RESET);
    continue;
  }
  return(x);
}
void clear(){
  if(system("@cls||clear")!=0){puts("error");}
  return;
}
void drawGraph(int resolution,float cor[2][resolution-1]){
  int color = graphColor(false);
  register int i;
  register int j;
  printf("\n\n");
  int corSize = 100;
  int halfRes = ((resolution-1)>>1);
  int res = resolution-1;
  char (*graph)[resolution];
  graph = malloc(sizeof(char[resolution][resolution]));
  
  /*initialize graph using nested loop for both axes
  preset all 'char' indices to their int value to avoid double-typecasting 1000 times*/
  for(i=0;i<resolution;i++){
    for(j=0;j<resolution;j++){
      graph[i][j] = 32;         // ' ' empty space
    }
  }
  for(i=0;i<(resolution);i++){
    graph[halfRes][i] = 126;    // '~'
    
    graph[i][halfRes] = 124;    // '|'
  }
  graph[halfRes][halfRes] = 43; // '+'
  for(i = 0;i<halfRes;i+=5){
    graph[halfRes][i] = 124;    // '|'
    graph[i][halfRes] = 45;     // '-'
  }
  for(i = (resolution-1); i>halfRes;i-=5){
    graph[halfRes][i] = 124;    // '|'
    graph[i][halfRes] = 45;     // '-'
  }
  for(register int n = 0; n<corSize;n++){
    float y = cor[0][n];
    float x = cor[1][n];
    if(y>10){
      continue;
    }
    if(y<-10){
      continue;
    }
    if(y==500){
      continue;
    }
      if(x<0){
        x = (50-((x*-10)/2));
      }
      else{
        x = (50+((x*10)/2));
      }
      if(y<0){
        y = (50+((y*-10)/2));
      }
      else{
        y = (50-((y*10)/2));
      }
    x = (floorf(x)*100)/100;
    y = (floorf(y)*100)/100;
    graph[(int)(y)][(int)(x)] = 35; // '#'
  }
  //uses math to take float and convert it to printable position in graph array with some loss of precision
  //graph formatting spaghetti
  //at least it stays formatted
  //C hates ASCII so I'm forced to use UTF-8
  for(register int i=0;i<resolution;i++){
    for(register int j=0;j<resolution;j++){
      switch(graph[i][j]){
        case '-': 
          switch(i){
            case 0:
              printf("%ls",L"┬");
              break;
            case (100):
              printf("%ls",L"┴");
              break;
            default:
              printf("%ls",L"┼");
              break;
          }
          break;
        case '|': 
          if(i==(halfRes)){
            switch(j){
              case 0:
                printf("%ls",L"├");
                break;
              case (100):
                printf("%ls",L"┤");
                break;
              default:
                printf("%ls",L"┼");
                break;
            }
          }
          else{printf("%ls",L"│");}

          
          break;
        case '~': 
          printf("%ls",L"─");
          break;
        case '+':
          printf("%ls",L"┼");
          break;
        default:
          PRINTC(color,"%c",graph[i][j]);
          break;
      }
      if(j==(resolution-1)){
        printf("\n");
      }
    }
  }
  free(graph);
  char wait;
  printf("Type " ANSI_COLOR_YELLOW "X" ANSI_COLOR_RESET " to return to menu\n\n" ANSI_COLOR_YELLOW ">" ANSI_COLOR_RESET);
  if(scanf(" %c",&wait)!=0){puts("Type X error");}
  menu();
}
void linear(float list[2][100]){
  //literally cannot print with more precision than 0.2 without doubling the resolution
  //problem

  //negative slope orbits the origin but never sits on the y intercept properly - low attention - only on function 1
  clear();
  float m = 1;
  float b = 0;
  printf(ANSI_COLOR_YELLOW "Enter value for slope\n\n> " ANSI_COLOR_RESET);
  m = validInput(" ");
  printf(ANSI_COLOR_YELLOW "Enter value for y intercept\n\n> " ANSI_COLOR_RESET);
  b = validInput(" ");
  register float x = -10;
  for(register int i = 0;i<100;i++){
    
    //round up to prevent double printing from floating point errors
    list[1][i] = ceilf(x*100)/100;
    list[0][i] = ceilf(((m*x)+b)*100)/100;
    x +=0.2;
  }
  drawGraph(101,list);
  free(list);
  
  return;
}

void quadratic(float list[2][100]){
  //f(x) = a(x-h)^2 + k
  clear();
  float (*vars);
  char (*varName);
  vars = malloc(4*sizeof(float));
  varName = malloc(5*sizeof(char));
  strcpy(varName,"ahki"); 
  for(register int i = 0;i<4;i++){
    printf(ANSI_COLOR_YELLOW "Enter value for %c:\n\n> " ANSI_COLOR_RESET,varName[i]);
  vars[i] = validInput(" ");
  }
  
  free(varName);
  float (*xptr) = malloc(sizeof(float));
  *xptr = -10;
  float x = *xptr;
  for(register int i=0;i<100;i++){
    list[1][i] = ceilf(x*100)/100;
    float firstIter = pow((x-vars[1]),vars[3]);
    float secondIter = (vars[0]*firstIter)-vars[2];
    list[0][i] = ceilf(secondIter*100)/100;
    x+=0.2;
  }
  drawGraph(101,list);
  free(list);
  free(xptr);
  return;
  
}
void sine(float list[2][100]){
  /*f(x) = A·sin(B(x-C)) + D
  A: amplitude
  B: affects period
  C: phase shift
  D: vertical shift
  a good testing value is: a = 3; b = 1; c = 0; d = 0
  if b is too large the wave becomes unintelligible due to the low resolution of the graph
  */
  clear();
  char (*varName);
  double (*vars);
  varName = malloc(5*sizeof(char));
  vars = malloc(4*sizeof(double));
  strcpy(varName, "abcd");
  for(register int i = 0;i<4;i++){
    printf(ANSI_COLOR_YELLOW "Enter value for %c\n\n> " ANSI_COLOR_RESET, varName[i]);
    vars[i] = validInput(" ");
  }
  free(varName);
  float (*xptr) = malloc(sizeof(float));
  *xptr = -10;
  float x = *xptr;
  for(register int i = 0;i<100;i++){
    list[1][i] = ceilf(x*100)/100;
    float firstIter = (x-vars[2]);  //B(x-c)
    float secondIter = sin(firstIter*vars[1])*vars[0]+vars[3]; //A(sin(n))+D
    list[0][i] = ceilf(secondIter*100)/100;
    x+=0.2;
  }
  drawGraph(101,list);
  free(list);
  free(xptr);
  return;
}
void tangent(float list[2][100]){
  //f(x)=Atan(Bx)
  char (*varName);
  double (*vars);
  vars = malloc(2*sizeof(double));
  varName = malloc(3*sizeof(char));
  strcpy(varName,"ab");
  for(register int i = 0;i<2;i++){
    printf(ANSI_COLOR_YELLOW "Enter value for %c\n\n>" ANSI_COLOR_RESET, varName[i]);
    vars[i] = validInput(" ");
  }
  float (*xptr) = malloc(sizeof(float));
  *xptr = -10;
  float x = *xptr;
  for(register int i = 0;i<100;i++){
    list[1][i] = ceilf(x*100)/100;
    float firstIter = vars[1]*x;
    float secondIter = vars[0]*tan(firstIter);
    list[0][i] = ceilf(secondIter*100)/100;
    x+=0.2;
  }
  drawGraph(101,list);
  free(list);
  free(xptr);
  return;
}

void list_init(char enteredFrom){
  float (*list)[100];
  list = malloc(sizeof(float[2][100]));
  for(register int i = 0;i<100;i++){
    for(register int j = 0;j<2;j++){
      list[j][i] = 500;
    }
  }
  switch(enteredFrom){
    case 'l':
        linear(list);
        break;
    case 'q':
        quadratic(list);
        break;
    case 's':
        sine(list);
        break;
    case 't':
        tangent(list);
        break;
    default:
        puts("big error");
        break;
  }
  return;
}
void startAscii(){
  printf( ANSI_COLOR_MAGENTA
    "                                   KKKKKKKKKKKKK                   \n"
    "                                     KKKKK     KKKK                \n"
    "                                         KK       KKK         K    \n"
    "                                          KK        KK        KKK  \n"
    "                                           K         KK       K KK \n"
    "                                           K          KK      K  K \n"
    "                                           K  ~~~      K     KK  K \n"
    "                                           K  ~~~~~    KK    K   K \n"
    "                                           K  ~~~~~~   KK   K    K \n"
    "                              KKKK       KKK  ~~~~~~   K   KK    K \n"
    "                            KKK        KKK  ~~~~~~~~  KK  K      K \n"
    "                          KKKK       KKK  ~~~~~~~~~~ KK KK   ~~  KK\n"
    "                        KKK  KK    KKK   ~~~~~~~~~~~ KKK    ~~~   K\n"
    "                        K  ~~ KKKK     ~~~~~~~~~~~~~~    ~~~~~~   K\n"
    "                       KK ~~      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  K\n"
    "                       K ~~~~~~~~~~~~~   #######        ~~~~~~~~  K\n"
    "                       K ~~~~~~~~ #######      #########    ~~~~  K\n"
    "                       K ~~~~~ ###   ++          ++     ####   ~ KK\n"
    "                       K  ~~###     ++            +         ##   K \n"
    "                       K  ###       +     @@@     +           ##KK \n"
    "                       K ##         +    @@@@@    +            ##  \n"
    "                       K#           +     @@@     +           ###  \n"
    "                       ##           +            +          #####  \n"
    "                       ####         +           +        ########  \n"
    "                       ##########   +         #################    \n"
    "                         ###################################       \n"
    "                           ############################            \n"
    "                                  #############                    \n" ANSI_COLOR_RESET
  );
  printf(ANSI_COLOR_RED
    "                                                                                          $$$$$$$$\n"
    "                                                               $                      $$$$$$$$$$  \n"
    "                                                           $$$$$                      $$$$        \n"
    "                                       $$$$$   $$    $$ $$$$$                         $           \n"
    "   $$$$$   $$$$$$$$$$           $    $$$    $$ $$    $$ $$                 $          $           \n"
    "  $$       $        $          $$     $      $ $$    $$  $     $$$        $$      $$  $      $$   \n"
    " $$$       $        $         $$$$    $     $$ $$  $$$$  $$  $$$         $$$     $$   $ $$$$$$    \n"
    "$ $        $   $$$$$$        $$  $    $$$$$$   $$ $$ $$   $$$$          $$ $    $$    $$$$        \n"
    "$ $        $   $$          $$$   $    $$$      $$$$  $$   $            $$  $   $$     $$          \n" //The N accidentially looks like the azov logo which is a MASSIVE oopsie
    "$ $$       $ $$  $$        $     $     $$      $$$   $$   $$          $$$  $  $$      $       $$  \n" //I swear I was just tryna make an angled N
    "$  $ $$$$  $ $$$  $$      $      $$    $$      $$    $$    $  $$$$$$  $$   $ $$$      $   $$$$    \n"
    "$  $$$  $  $ $ $$  $$    $$       $    $$      $$    $$    $$$$      $$    $$$$       $ $$$       \n"
    "$   $$$ $  $ $  $$  $$  $$        $$   $$      $$    $$    $$        $     $$$        $$$         \n"
    "$$    $$$  $$$   $$$$$$ $$$$$$$$$$$$                                       $          $           \n"
    "  $$$$$                                                                                           \n" ANSI_COLOR_RESET
  );
}
void menu(){
  clear();
  startAscii();
  int color = graphColor(false);
  char displayedColor[8];
  switch(color){
    case 95:
      strcpy(displayedColor, "Magenta");
      break;
    case 94:
      strcpy(displayedColor, "Blue");
      break;   
    case 31:
      strcpy(displayedColor, "Red");
      break;
  }
  int (*selection);
  int c;
  selection = malloc(sizeof(int));
  //ascii art
 
  printf("\n\n\n\nFunctions:\n\n " ANSI_COLOR_BLUE "1 - Linear    | f(x) = mx+b\n 2 - Quadratic | f(x) = a(x - h)%ls + k\n 3 - Sine Wave | f(x) = A·sin(B(x-C)) + D \n 4 - Tangent   | f(x) = A·tan(Bx)\n\n" ANSI_COLOR_RESET,L"ͥ ");
  printf(ANSI_COLOR_CYAN" 5 - Graph Color: " ANSI_COLOR_RESET);
  PRINTC(color, "%s\n\n\n", displayedColor);
  printf(ANSI_COLOR_YELLOW "Enter selection:\n\n> " ANSI_COLOR_RESET);
  *selection = validInput(" ");
  clear();
  switch(*selection){
    case 1:
        list_init('l');
        break;
    case 2:
        list_init('q');
        break;
    case 3:
        list_init('s');
        break;
    case 4:
        list_init('t');
        break;
    case 5:
        if(graphColor(true)!=0){puts("graph setting error");}
        menu();
        break;
    default:
        menu();
        break;
  }
  free(selection);
  return;
}






int main(void) {
  //clear();
  setlocale(LC_ALL, "");
  menu();
  return 0;
  }
