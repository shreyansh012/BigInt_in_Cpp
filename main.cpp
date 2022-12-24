#include <bits/stdc++.h>
using namespace std;

class bigint
{
private:
public:
    string num;
    bigint()
    {
        num = "0";
    }
    bigint(string num)
    {
        this->num = num;
    }
    // bigint(const char *s)
    // {
    //     num = "";
    //     for (int i = strlen(s) - 1; i >= 0; i--)
    //         num.push_back(s[i] - '0');
    // }
    void operator =(string a){
        this->num=a;
    }
};
//Constructor Overloading
bigint operator + (const bigint &b1, const bigint &b2)
{
    string a = b1.num;
    string b = b2.num;
    int n1 = a.size();
    int n2 = b.size();
    int n;

    string ans;
    if (n1 > n2)
        ans = a, n = n1;
    else
        ans = b, n = n2;

    int carry = 0;
    int i = n1 - 1;
    int j = n2 - 1;
    int ai = n - 1;

    while (i >= 0 && j >= 0)
    {
        int o1 = a[i] - '0';
        int o2 = b[j] - '0';

        char toPut = (char)('0' + ((o1 + o2 + carry) % 10));
        carry = (o1 + o2 + carry) / 10;

        ans[ai] = toPut;

        ai--;
        i--;
        j--;
    }

    while (i >= 0)
    {
        int o1 = (int)a[i] - '0';
        int o2 = 0;

        char toPut = (char)('0' + ((o1 + o2 + carry) % 10));
        carry = (o1 + o2 + carry) / 10;

        ans[ai] = toPut;

        ai--;
        i--;
    }

    while (j >= 0)
    {
        int o1 = 0;
        int o2 = (int)b[j] - '0';

        char toPut = (char)('0' + ((o1 + o2 + carry) % 10));
        carry = (o1 + o2 + carry) / 10;

        ans[ai] = toPut;

        ai--;
        j--;
    }

    if (carry)
    {
        string temp = ans;
        ans = (carry + '0');
        ans += temp;
    }
    bigint ans1(ans);
    return ans1;
}

bool isSmaller(string str1, string str2)
{
    // Calculate lengths of both string
    int n1 = str1.length(), n2 = str2.length();

    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;

    for (int i = 0; i < n1; i++)
    {
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
    }
    return false;
}

bigint operator - (bigint &b1, bigint &b2)
{
    string str1 = b1.num;
    string str2 = b2.num;
    if (isSmaller(str1, str2))
        swap(str1, str2);

    // Take an empty string for storing result
    string str = "";

    // Calculate lengths of both string
    int n1 = str1.length(), n2 = str2.length();
    int diff = n1 - n2;

    // Initially take carry zero
    int carry = 0;

    // Traverse from end of both strings
    for (int i = n2 - 1; i >= 0; i--)
    {
        // Do school mathematics, compute difference of
        // current digits and carry
        int sub = ((str1[i + diff] - '0') - (str2[i] - '0') - carry);
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    // subtract remaining digits of str1[]
    for (int i = n1 - n2 - 1; i >= 0; i--)
    {
        if (str1[i] == '0' && carry)
        {
            str.push_back('9');
            continue;
        }
        int sub = ((str1[i] - '0') - carry);
        if (i > 0 || sub > 0) // remove preceding 0's
            str.push_back(sub + '0');
        carry = 0;
    }

    // reverse resultant string
    reverse(str.begin(), str.end());

    return str;
}

bigint operator * (bigint &b1, bigint &b2)
{
    string num1 = b1.num;
    string num2 = b2.num;
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return (string)"0";
 
    // will keep the result number in vector
    // in reverse order
    vector<int> result(len1 + len2, 0);
 
    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;
     
    // Go from right to left in num1
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
 
        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;
         
        // Go from right to left in num2            
        for (int j=len2-1; j>=0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j] - '0';
 
            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
 
            // Carry for next iteration
            carry = sum/10;
 
            // Store result
            result[i_n1 + i_n2] = sum % 10;
 
            i_n2++;
        }
 
        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
 
        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }
 
    // ignore '0's from the right
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
 
    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
    return (string)"0";
 
    // generate the result string
    string s = "";
     
    while (i >= 0)
        s += std::to_string(result[i--]);
 
    return s;
}


bigint operator / (bigint &b1, int divisor)
{
    string ans;
    string number = b1.num;
    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');

    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx)
    {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';

        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }

    // If divisor is greater than number
    if (ans.length() == 0)
        return (string)"0";

    // else return ans
    return ans;
}

bigint pow(bigint &num, int power){
    if(power==0) return (string)"1";
    if(power==1) return num;

    bigint ans;
    if(power%2) 
	{		
			ans = pow(num,power-1);
			ans = num * ans;
	}
	else
	{
			bigint temp = pow(num , power/2 );
			ans = temp * temp;
	}

	return ans;
}


bigint Factorial(int n){
    bigint f("1");
    for (int i = 2; i <= n;i++){
        string s=to_string(i);
        bigint g(s);
        bigint a=f*g;
        f=a;
    }
    return f;
}


int main()
{
    bigint b1,b2;       //declaring the bigint datatype variables
    b1="500009868758567686787685875858755800";        //assigning values to the variables (the variable values should be assigned in the form of a string only)
    b2="12371623912837412941827451294678612549127845219487211293487";
   //Adding two big integers
    bigint ans=b1+b2;
    cout<<"The sum of "<<b1.num<<" and "<<b2.num<<" is: "<<ans.num<<endl;
    cout<<endl;

    //Subtracting two big integers
    ans=b1-b2;
    cout<<"The difference of "<<b1.num<<" and "<<b2.num<<" is: "<<ans.num<<endl;
    cout<<endl;

    //Multiplying two big integers
    ans=b1*b2;
    cout<<"The product of "<<b1.num<<" and "<<b2.num<<" is: "<<ans.num<<endl;
    cout<<endl;

    //Dividing a big integer with and ineteger
    ans=b1/1000000;
    cout<<"The result of "<<b1.num<<" divided by 1000000 is:  "<<ans.num<<endl;
    cout<<endl;

    //Calculating the power of a big integer
    bigint b3("999");
    ans=pow(b3,10);
    cout<<"The result of 999 raised to the power 10 (999^10) is: " <<ans.num<<endl;
    cout<<endl;

    //Factorial of an integer
    int n=150;
    ans=Factorial(n);
    cout<<"The factorial of "<<n<<" is: "<<ans.num<<endl;
    cout<<endl;
    return 0;
}
