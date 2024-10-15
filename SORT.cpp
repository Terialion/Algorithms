#include <iostream>
#include <vector>

#define INT_MAX 10000
class Sort
{
private:
    void INSERTION_SORT(std::vector<int>& A)//ch2.2
    {
        for (int j = 1; j < A.size(); j++)
        {
            auto key = A[j];
            int i = j - 1;
            while (i >= 0 && A[i] > key)
            {
                A[i + 1] = A[i];
                i--;
            }
            A[i + 1] = key;
        }
    }
    void MERGE(std::vector<int>& A, int p, int q, int r)//ch2.3.1
    {
        auto n1 = q - p + 1;
        auto n2 = r - q;
        std::vector<int> L(n1 + 1, 0);
        std::vector<int> R(n2 + 1, 0);
        for (int i = 0; i < n1; i++)
        {
            L[i] = A[p + i];
        }
        for (int j = 0; j < n2; j++)
        {
            R[j] = A[q + j + 1];
        }
        L[n1] = INT_MAX;
        R[n2] = INT_MAX;
        int i = 0;
        int j = 0;
        for (int k = p; k <= r; k++)
        {
            if (L[i] <= R[j])
            {
                A[k] = L[i];
                i++;
            }
            else
            {
                A[k] = R[j];
                j++;
            }
        }
    }
    void MERGESORT(std::vector<int>& A, int p, int r)//ch2.3.1
    {
        if (p < r)
        {
            auto q = (p + r) / 2;
            MERGESORT(A, p, q);
            MERGESORT(A, q + 1, r);
            MERGE(A, p, q, r);
        }
    }
    void BUBBLESORT(std::vector<int>& A)//ch2.3
    {
        for (int i = 0; i < A.size(); i++)
        {
            for (int j = A.size() - 1; j > i; j--)
            {
                if (A[j] < A[j - 1])
                {
                    std::swap(A[j], A[j - 1]);
                }
            }
        }
    }
    int PARTITION(std::vector<int>& A, int p, int r)
    {
        auto x = A[r];
        auto i = p - 1;
        for (int j = p; j <= r - 1; j++)
        {
            if (A[j] <= x)
            {
                i++;
                std::swap(A[i], A[j]);
            }
        }
        std::swap(A[i + 1], A[r]);
        return i+1;
    }
    void QUICKSORT(std::vector<int>& A, int p, int r)
    {
        if (p < r)
        {
            auto q = PARTITION(A, p, r);
            QUICKSORT(A, p, q - 1);
            QUICKSORT(A, q + 1, r);
        }
    }
    int RANDOMIZED_PARTITION(std::vector<int>& A, int p, int r)
    {
        auto i = rand() % (r - p + 1) + p;
        std::swap(A[r], A[i]);
        return PARTITION(A, p, r);
    }
    void RANDOMIZED_QUICKSORT(std::vector<int>& A, int p, int r)
    {
        if (p < r)
        {
            auto q = RANDOMIZED_PARTITION(A, p, r);
            RANDOMIZED_QUICKSORT(A, p, q - 1);
            RANDOMIZED_QUICKSORT(A, q + 1, r);
        }
    }
    void COUNTING_SORT(std::vector<int> A, std::vector<int>& B, int k)
    {
        std::vector<int> C(k + 1, 0);
        for (auto num : A)
        {
            C[num] = C[num] + 1;
        }
        for (int i = 1; i <= k; i++)
        {
            C[i] = C[i] + C[i - 1];
        }
        for (int j = A.size() - 1; j >= 0; j--)
        {
            B[C[A[j]]] = A[j];
            C[A[j]] = C[A[j]] - 1;
        }
    }
    void BUCKETSORT(std::vector<int>& A)
    {
        std::vector<int> B(A.size(), 0);
        //
    }
    public:
    void quicksort(std::vector<int>& A)
    {
        QUICKSORT(A, 0, A.size() - 1);
    }
    void randomized_quicksort(std::vector<int>& A)
    {
        RANDOMIZED_QUICKSORT(A, 0, A.size() - 1);
    }
};
class Statistics
{
    private:
    public:
};
int main()
{
    std::vector<int> nums = {5, 2, 8, 1, 3, 7, 6};
    Sort qs;
    qs.quicksort(nums);
    for (auto num : nums)
    {
        std::cout << num << " ";
    }
    system("pause");
    return 0;
}