#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<string.h>
#include<math.h>
char alphabet[26] = { 'a','b','c','d','e','f' ,'g','h','i' ,'j','k','l' ,'m','n','o' ,'p','q','r' ,'s','t','u' ,'v','w','x','y','z' };
struct Chi_squared_Statistic
{
    int shift;
    double stats;
};
struct LetterFrequency
{
    char letter;
    double stats;
};
struct StatsLetter {
    int count;
    char letter;
};
struct Index
{
    int time;
    double index;
};
LetterFrequency Freq[26] = { 'e',0.13,'t',0.091,'a',0.082,'o',0.075,'i',0.07,'n',0.067,'s',0.063,'h',0.061,'r',0.06,'d',0.043,'l',0.04,'c',0.028,'u',0.028,'m',0.024,'w',0.024,'f',0.022,'g',0.02,'y',0.02,'p',0.019,'b',0.015,'v',0.0098,'k',0.0078,'j',0.0015,'x',0.0015,'q',0.00095,'z',0.00074};
Chi_squared_Statistic Anal(char* mas);
void Scrambler();
StatsLetter* Analyze(char* mas2);
char* Decodewithkey(char* key,char* mas,int keylong,int textlong);
void Output(StatsLetter* mas);
int KeyLongGuesser(Index* mas);
int LongText(char* mas);
void Shift(char* mas);
void Decoder();
char* Coder(char* mas,char* keyword,int textlong,int kelong);
int LongTextFile(FILE* file);
char** Partition(int keylong, int longtext, char* GeneralMas);
char* WriteToArray(FILE* file,int longoftext,int fl);
double IndexOfCoincidence(int keylong, StatsLetter* letter, int longtext);
double AverageIndex(char** mas, int keylong, int longoftext, int longtext);
char* insert(char* str, FILE* file);
void KeySuesser(int keylong,char* mas,int longoftext,FILE* file);
int main()
{
    printf("1.Breaking the cipher\n2.Encrypt the text");
    int choise;
    scanf("%d",&choise);
    switch (choise)
    {
    case 1:
    Decoder();
        break;
    case 2:
    Scrambler();
    break;
    default:
        break;
    }
}
void Decoder()
{
    Index* indexstats;
    indexstats = (Index*)malloc(20 * sizeof(Index));
    StatsLetter* mas;
    StatsLetter* mas1;
    FILE* test;
    test = fopen("Indexofcoencidence.txt", "r+b");
    if (test == NULL)
    {
        printf("We didnt find file");
        exit(1);
    }
    char** partitionmas;
    char* text;
    int longoftext = LongTextFile(test);
    rewind(test);
    text = WriteToArray(test, longoftext,0);
    for (int i = 2; i < 100; i++)
    {
        int keylong = i;
        int longtext = longoftext / i;
        partitionmas = Partition(keylong, longoftext, text);
        double Index1, Index2, Index3;
        Index1 = AverageIndex(partitionmas, keylong, longoftext,longtext);
        indexstats[i].index = Index1;
        indexstats[i].time = i;
    }
    int a = KeyLongGuesser(indexstats);
    for (int i = 0; i < 26; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (Freq[j].letter < Freq[j - 1].letter)
            {
                LetterFrequency buf = Freq[j];
                Freq[j] = Freq[j - 1];
                Freq[j - 1] = buf;
            }
        }
    }
    KeySuesser(a, text, longoftext,test);
}
char* Decodewithkey(char* key,char* mas,int keylong,int textlong)
{
    rewind(stdin);
    char* textafter;
    textafter=(char*)malloc(textlong*sizeof(char));
    int i=0;
    int k=0;
    while (mas[i]!=0)
    {
        //printf("SOSI");
        if((mas[i]>='a' && mas[i]<='z')||(mas[i]>='A'&&mas[i]<='Z'))
        {
            //printf("sosi");
            if(mas[i]>='A'&&mas[i]<='Z')
            {
                mas[i]+=32;
            }
            int a=(((mas[i]-97)+26-(key[k]-97))%26)+97;
            //printf("%d",a);
            textafter[i]=a;
            k++;
            //printf("% d",k);
            if(k==keylong)
            k=0;
        }
        else
        {
            textafter[i]=mas[i];
        }
        i++;
    }
    textafter[i]=0;
    return textafter;
    
}
void Scrambler()
{
    FILE *fp;
    fp=fopen("textbefore.txt","r+b");
    char* textafter;
    char* cipher;
    char* keyword;
	char* mas;
    printf("\nInput text\n");
    rewind(stdin);
	int N = 2;
	char a;
	mas = (char*)malloc(N * sizeof(char));
	int i = 0;
	while ((mas[i] = getchar()) != '\n')
	{
		i++;
		N++;
		mas = (char*)realloc(mas, N*sizeof(char));
	}
	mas[i] = '\0';
    int textlong=i;
	printf("\n%s\n", mas);
    //printf("%s",textafter);
    N=2;
    printf("\nInput key word\n");
    keyword = (char*)malloc(N * sizeof(char));
	i = 0;
	while ((keyword[i] = getchar()) != '\n')
	{
		i++;
		N++;
		keyword= (char*)realloc(keyword, N*sizeof(char));
	}
	keyword[i] = '\0';
	printf("\n%s\n", keyword);
    int keylong=i;
    cipher=Coder(mas,keyword,textlong,keylong);
    printf("\n%s",cipher);
}
char *Coder(char* mas,char* keyword,int textlong,int kelong)
{
    rewind(stdin);
    char* Cipher;
    Cipher=(char*)malloc(textlong*sizeof(char));
    int i=0;
    int k=0;
    while (mas[i]!=0)
    {
        //printf("SOSI");
        if((mas[i]>='a' && mas[i]<='z')||(mas[i]>='A'&&mas[i]<='Z'))
        {
            //printf("sosi");
            if(mas[i]>='A'&&mas[i]<='Z')
            {
                mas[i]+=32;
            }
            int a=(((mas[i]-97)+(keyword[k]-97))%26)+97;
            //printf("%d",a);
            Cipher[i]=a;
            k++;
            //printf("% d",k);
            if(k==kelong)
            k=0;
        }
        else
        {
            Cipher[i]=mas[i];
        }
        i++;
    }
    Cipher[i]=0;
    return Cipher;
    
}
void KeySuesser(int keylong,char* mas,int longoftext,FILE* file)
{
    char** partition;
    Chi_squared_Statistic masstats[26];
    partition = Partition(keylong, longoftext, mas);
    //printf("KeyLong is %d", keylong);
    Chi_squared_Statistic minimum;
    char* keyword;
    keyword = (char*)malloc((keylong+1) * sizeof(char));
    for (int i = 0; i < keylong; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (j != 0)
            {
                Shift(partition[i]);
            }
            masstats[j] = Anal(partition[i]);
            masstats[j].shift = j;
        }
        for (int k = 0; k < 26; k++)
        {
            for (int h = k; h > 0; h--)
            {
                if (masstats[h].stats < masstats[h - 1].stats)
                {
                    Chi_squared_Statistic buf = masstats[h];
                    masstats[h] = masstats[h - 1];
                    masstats[h - 1] = buf;
                }
            }
        }
        //printf("Stats is %lf when shift is %c", masstats[0].stats, masstats[0].shift);
        keyword[i] = masstats[0].shift + 97;
        keyword[i + 1] = 0;
        //printf("hkjlasdjkhasd");
        //printf("Stats is %lf when %d shift\n", minimum.stats, minimum.shift);
    }
    printf("\nKEY WORD IS %s\n", keyword);
    char* result;
    int longkey=strlen(keyword);
    int textlong=strlen(mas);
    //printf("\n%s",mas);
    result=Decodewithkey(keyword,mas,longkey,longkey);
    result=insert(result,file);
    printf("\n%s",result);
}
char* insert(char* mas, FILE* file) {
    char a;
    int i=0;
    char* str=(char*)malloc(strlen(mas));
    while (mas[i]!=0)
    {
        str[i]=mas[i];
        i++;
    }
    str[i]='\0';
    fseek(file, 0, SEEK_SET);
    int indexinfile = 0;
    int size = strlen(str);
    int counter = 0;
    while ((a = getc(file)) != EOF) {
        if (a == ' ' || a == '.' || a == ',' || a == '?' || a == '-' || a == ':' || a == '\n' || a == '\'' || a == '(' || a == ')' || a == '!' || a == '"' || (a >= '1' && a <= '9') || a == ';') {
            counter++;
            str = (char*)realloc(str, size + 2);
            for (int i = size; i > indexinfile; i--) { 
                str[i] = str[i - 1];
            }
            str[indexinfile] = a;
            size++;
            int j=0;
        }
        indexinfile++;
    }
    return str;
}
Chi_squared_Statistic Anal(char *mas)
{
    rewind(stdin);
    Chi_squared_Statistic stat;
    StatsLetter* statintext;
    statintext = Analyze(mas);
    stat.stats = 0;
    //Output(statintext);
    int longtext = strlen(mas);
    double square = 0;
    double a;
    double b;
    double c;
    double d;
    for (int i = 0; i < 26; i++)
    {
        stat.stats += (pow((statintext[i].count - Freq[i].stats * longtext),2) / (Freq[i].stats * longtext));
    }
    return stat;
}
void Shift(char* mas)
{
    for (int i = 0; mas[i]!=0; i++)
    {
        if(mas[i]>'a')
        mas[i] -= 1;
        else
        {
            mas[i] = 'z';
        }
    }
}
int KeyLongGuesser(Index* mas)
{
    double a, b;
    double etalon = 0.0667;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 24; j > i; j--)
        {
            a = ((mas[j].index) - etalon);
            b = ((mas[j - 1].index) - etalon);
            if (fabs(a)<fabs(b))
            {
                Index buf = mas[j - 1];
                mas[j - 1] = mas[j];
                mas[j] = buf;
            }
        }
    }
    /*for (int i = 0; i < 24; i++)
    {
        printf("\nIndex %lf when keylong is %d",mas[i].index,mas[i].time);
    }*/
    int fl = 0;
    int j = 0;
    int count = 0;
    int fl1=0;
    int k = 0;
    int keylong = mas[0].time;
    while (mas[j].index > 0.06000)
    {
        if (mas[j].time < keylong)
        {
            keylong = mas[j].time;
        }
        j++;
    }
    //printf("\nKEYLONG is %d", keylong);
    return keylong;
}
StatsLetter* Analyze(char* mas2)
{
    StatsLetter* mas;
    mas = (StatsLetter*)malloc(26 * sizeof(StatsLetter));
    for (int i = 0; i < 26; i++)
    {
        mas[i].count = 0;
        mas[i].letter = alphabet[i];
    }
    char a;
    int j = 0;
    while (mas2[j]!=0)
    {
        a = mas2[j];
        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
        {
            if (a >= 'A' && a <= 'Z')
            {
                a += 32;
            }
            for (int i = 0; i < 26; i++)
            {
                if (a == mas[i].letter)
                {
                    mas[i].count++;
                }
            }
        }
        j++;
    }
    return mas;
}
void Output(StatsLetter *mas)
{
    //printf("\n");
    for (int i = 0; i < 26; i++)
    {
        //printf("Letter %c occurs in text %d times\n", mas[i].letter, mas[i].count);
    }
}
char** Partition( int keylong, int longtext, char *GeneralMas)
{
    char** mas;
    mas = (char**)malloc(keylong * sizeof(char*)); //we have error
    for (int i = 0; i < keylong; i++)
    {
        mas[i] = (char*)malloc((longtext / keylong) * sizeof(char));
    }
    int k = 0;
    for (int j = 0; j < keylong; j++)
    {
        k = 0;
        for (int i = j;GeneralMas[i]!='\0'; i+=keylong)
            {
                mas[j][k] = GeneralMas[i];
                    k++;
            }
        mas[j][k-1] = 0;
    }
    return mas;
}
int LongText(char* mas)
{
    rewind(stdin);
    int i = 0;
    int a;
    while (mas[i]!=0)
    {
        a = mas[i];
        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
        i++;
    }
    return i;
}
char* WriteToArray(FILE* file,int longoftext,int fl)
{
    rewind(file);
    rewind(stdin);
    char* mas = (char*)malloc((longoftext+2) * sizeof(char));
    char a;
    int i = 0;
    while ((a = getc(file)) != EOF)
    {
        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')&&fl==0) {
            mas[i] = a;
            i++;
        }
        else if(fl==1)
        {
            mas[i] = a;
            i++;
        }
    }
    mas[i] = 0;
    return mas;
}
double IndexOfCoincidence(int keylong,StatsLetter* letter,int longtext)
{
    double IndexOfCoincidence = 0;
    double long1 = longtext;
    for (int i = 0; i < 26; i++)
    {
        IndexOfCoincidence += ((letter[i].count) / long1) * (((letter[i].count) - 1) / (long1 - 1));
    }
    return IndexOfCoincidence;
}
double AverageIndex(char **mas, int keylong, int longoftext, int longtext)
{
    double Average = 0;
    int* mas3 = (int*)malloc(keylong * sizeof(int));
    StatsLetter** Stats;
    Stats = (StatsLetter**)malloc(keylong * sizeof(StatsLetter));//we have error there
    for (int i = 0; i < keylong; i++)
    {
        Stats[i] = Analyze(mas[i]);
    }
    double* index;
    index = (double*)malloc(keylong * sizeof(double));//we have error
    for (int i = 0; i < keylong; i++)
    {
        index[i] = 0;
    }
    for (int i = 0; i < keylong; i++)
    {
        index[i] = IndexOfCoincidence(3,Stats[i],longtext);
        //printf("Index is %lf", index[i]);
    }
    for (int i = 0; i < keylong; i++)
    {
        Average += index[i];
    }
    Average /= keylong;
    return Average;
}
int LongTextFile(FILE* file) {
    char a;
    int i = 0;
    while ((a = getc(file)) != EOF)
    {
        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
        {
            i++;
        }
    }
    return i;
}