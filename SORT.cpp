#include <iostream>
#include <vector>

class Sort
{
private:
    void INSERTION_SORT(std::vector<int> A)
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