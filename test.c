#include <stdio.h>
#include <stdlib.h>

const int N = 1e4 + 10;

typedef struct 
{
    int m_Id;
    int m_Age;
    char *m_Name;
} Student;

typedef struct 
{
    Student students[N];
    int index;
} StuList;

void init(StuList *L, char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        L->index = 0;
        return;
    }

    fread(L->index, sizeof(int), 1, file);
    fread(L->students, sizeof(Student), L->index, file);

    fclose(file);

    return;
}

// 功能项 1
void func1(StuList *L)
{
    int Stu_Id;

    printf("请输入第一位学生的学号\n");
    scanf("%d", &Stu_Id);

    for (int i = 1; i <= 5; i ++ )
    {
        L->students[L->index].m_Id = Stu_Id ++ ;
        printf("请输入第%d位学生的姓名\n", i);
        scanf("%s", L->students[L->index].m_Name);
        printf("请输入第%d位学生的年龄\n", i);
        scanf("%d", L->students[L->index ++ ].m_Age);
    }

    return;
}

// 功能项 2
void func2(const StuList *L, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Fail to open the file.");
        exit(EXIT_FAILURE);
    }

    fwrite(&(L->index), sizeof(int), 1, file);
    fwrite(&(L->students), sizeof(Student), L->index, file);

    fclose(file);
}

// 功能项 3
void func3(const StuList *L, const char *input_file, const char *output_file)
{
    FILE *file = fopen(input_file, "rb");
    if (file == NULL)
    {
        perror("Fail to open the file.");
        exit(EXIT_FAILURE);
    }

    fread(L->index, sizeof(int), 1, file);
    fread(L->students, sizeof(Student), L->index, file);

    fclose(file);

    file = fopen(output_file, "wb");
    if (file == NULL)
    {
        perror("Fail to open the file.");
        exit(EXIT_FAILURE);
    }

    fwrite(&(L->index), sizeof(int), 1, file);
    for (int i = L->index - 1; i >= 0; i -- )
    {
        fwrite(&(L->students[i]), sizeof(Student), 1, file);
    }

    fclose(file);
}

int main()
{
    StuList L;

    init(&L, "save_dat");

    func1(&L);

    func2(&L, "save.dat");

    func3(&L, "save.dat", "reverse.dat");
    
    return 0;
}
