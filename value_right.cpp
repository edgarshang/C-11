#include <iostream>
#include <string.h>
#include <vector>
#include <type_traits>

using namespace std;


#if 0
int g_constructCount = 0;
int g_copyConstructCount = 0;
int g_destructCount = 0;

struct A
{
    A()
    {
        cout << "construct: " << ++g_constructCount << endl;
    }

    A(const A& a)
    {
        cout << "copy construct: " << ++g_copyConstructCount << endl;
    }

    ~A()
    {
        cout << "destruct: " << ++g_destructCount << endl;
    }
};

A GetA()
{
    return A();
}

class B
{
private:
    int *m_ptr;
public:
    B():m_ptr(new int(0))
    {
        cout << "construct" << endl;
    }
    B(const B& a):m_ptr(new int(*a.m_ptr))
    {
        cout << "copy construct" << endl;
    }
    B(B&& a):m_ptr(a.m_ptr)
    {
        a.m_ptr = nullptr;
        cout << "move construct" << endl;
    }
    ~B()
    {
        if(m_ptr == nullptr)
        {
            std::cout << "m_ptr == nullptr" << std::endl;
        }
        delete m_ptr;
        cout << "destruct" << endl;
    }
};

B GetB()
{
    return B();
}

class MyString{
    private:
        char *m_data;
        size_t m_len;
        void copy_data(const char* s)
        {
            m_data = new char[m_len+1];
            memcpy(m_data, s, m_len);
            m_data[m_len] = '\0';
        }
    public:
        MyString()
        {
            m_data = nullptr;
            m_len = 0;
        }

        MyString(const char *s)
        {
            m_len = strlen(s);
            copy_data(s);
        }

        MyString(const MyString &str)
        {
            m_len = str.m_len;
            copy_data(str.m_data);
            cout << "Copy Struct is called! source: " << str.m_data << endl;
        }

        MyString& operator=(const MyString& str)
        {
            if (this != &str)
            {
                m_len = str.m_len;
                copy_data(str.m_data);
            }
            cout << "Copy Assignment is called! source: " << str.m_data << endl;
            return *this;
        }

        MyString(MyString && str)
        {
            cout << "Move Constructor is called! source: "<< str.m_data << endl;
            m_len = str.m_len;
            m_data = str.m_data;

            str.m_len = 0;
            str.m_data = nullptr;
        }

        MyString &operator=(MyString &&str)
        {
            cout << "Move Assisgnment is called! source: " << str.m_data << endl;
            if(this != &str)
            {
                m_len = str.m_len;
                m_data = str.m_data;

                str.m_data = nullptr;
                str.m_len = 0;
            }

            return *this;
        }

        virtual ~MyString()
        {
            if(m_data)
            {
                delete []m_data;
            }
        }
};
void test_MyString()
{
    MyString a;
    a = MyString("Hello");
    vector<MyString> vec;
    vec.push_back(MyString("world"));
}

struct A
{
    int x;
    double y;
   A(int a, double b):x(a), y(b){}
};

int test(void )
{
    vector<A> v;
    v.emplace_back(1, 2);
    v.emplace_back(2, 3);
    cout << v.size() << endl;
    return 0;
}
class A{

};

class B : public A
{

};

class C{};
#endif






// int main(int argc, const char** argv) {
//     unsigned char *buf = new unsigned char[1024];
//     unsigned char encrypt_xor[4] = {0x41, 0x94, 0x31, 0x42};
    
//     cout << "sizeof(buf) = " << sizeof(buf) << endl;

//     auto encByte = [](unsigned char *data, int length) {
        
       
//         for (size_t i = 0; i < length; i++)
//         {
//             cout << data[i] << endl;
//             cout << "hello, world" << endl;
//         }
//     };

//     encByte(encrypt_xor, 4);

//     return 0;
// }

// int main(int argc, char const *argv[])
// {

//     if(argc != 3)
//     {
//         cout << "****************************************************************************************************************" << endl;
//         cout << "Usage:./a.out encFile(Compressed file input) decFile(output Decrypt the file whose name you set endwith .tar.gz)" << endl;
//         cout << "****************************************************************************************************************" << endl;
//         return -1;
//     }

    
//     FILE *fp = fopen(argv[1], "r");
//     if(fp != nullptr)
//     {
        
//     }else
//     {
//         cout << argv[1] << " is not exist" << endl;
//         return -1;
//     }

//     fseek(fp, 0L, SEEK_END);
//     int size = ftell(fp);
//     fseek(fp, 0L, SEEK_SET);

//     cout << argv[1] << " size = " << size << endl;
//     unsigned char *buffer = new unsigned char[size + 1024];
//     if (buffer == nullptr)
//     {
//         cout << "no enough memory" << endl;
//         return -1;
//     }
    
//     int readSize = fread(buffer, 1, size, fp);

//     cout << "read_size = " << readSize << endl;

//     unsigned char encrypt_xor[4] = {0x41, 0x94, 0x31, 0x42};

//     for (int index = 0; index < readSize; index++)
//     {
//         buffer[index] = buffer[index] ^ encrypt_xor[index % 4];
//         buffer[index] = ~buffer[index];
//     }

//     fclose(fp);

    
//     fp = fopen(argv[2], "w+");

//     if( fp != nullptr)
//     {
        
//     }else
//     {
//         cout << argv[2] << "open failed" << endl;
//         return -1;
//     }

//     int writeSize = fwrite(buffer, 1, size, fp);
//     cout << "write_size = " << writeSize << endl;
    

//     fclose(fp);

//     cout << "running successfully" <<endl;



//     return 0;
// }




