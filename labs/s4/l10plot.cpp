#include <iostream>
#include <set>
#include <random>
#include <vector>
#include <fstream>

class State
{
public:
    virtual bool contains(int t) const = 0;
};

class DiscreteState : public State
{
private:
    int const state;

public:
    DiscreteState() : state(0) {}
    DiscreteState(int state) : state(state) {}
    ~DiscreteState() {}
    bool contains(int s) const
    {
        return s == state;
    }
};

class SegmentState : public State
{
private:
    int const beg, end;

public:
    SegmentState() : beg(0), end(-1) {}
    SegmentState(int beg, int end) : beg(beg), end(end) {}
    ~SegmentState() {}
    bool contains(int s) const
    {
        return s >= beg && s <= end;
    }
};

class SetState : public State
{
private:
    std::set<int> const states;

public:
    SetState() : states() {}
    ~SetState() {}
    SetState(std::set<int> const &src) : states(src) {}
    bool contains(int s) const
    {
        return states.count(s) > 0;
    }
};

class SetsSupperPostion : public State
{
protected:
    State *state1;
    State *state2;

public:
    SetsSupperPostion() : state1(), state2() {}
    SetsSupperPostion(State &st1, State &st2)
    {
        state1 = &st1;
        state2 = &st2;
    }
    SetsSupperPostion(int beg1, int end1, int beg2, int end2)
    {
        state1 = new SegmentState(beg1, end1);
        state2 = new SegmentState(beg2, end2);
    }
    SetsSupperPostion(int beg1, int end1, int v1)
    {
        state1 = new SegmentState(beg1, end1);
        state2 = new DiscreteState(v1);
    }
    SetsSupperPostion(int beg1, int end1, std::set<int> const &src)
    {
        state1 = new SegmentState(beg1, end1);
        state2 = new SetState(src);
    }
    SetsSupperPostion(std::set<int> const &src1, std::set<int> const &src2)
    {
        state1 = new SetState(src1);
        state2 = new SetState(src2);
    }
    SetsSupperPostion(std::set<int> const &src1, int v1)
    {
        state1 = new SetState(src1);
        state2 = new DiscreteState(v1);
    }
    ~SetsSupperPostion()
    {
        delete state1;
        delete state2;
    }
};

class SetsDifferState : public SetsSupperPostion
{
public:
    SetsDifferState() : SetsSupperPostion() {}
    SetsDifferState(State &st1, State &st2) : SetsSupperPostion(st1, st2) {}
    SetsDifferState(int beg1, int end1, int beg2, int end2) : SetsSupperPostion(beg1, end1, beg2, end2) {}
    SetsDifferState(int beg1, int end1, int v1) : SetsSupperPostion(beg1, end1, v1) {}
    SetsDifferState(int beg1, int end1, std::set<int> const &src) : SetsSupperPostion(beg1, end1, src) {}
    SetsDifferState(std::set<int> const &src1, std::set<int> const &src2) : SetsSupperPostion(src1, src2) {}
    SetsDifferState(std::set<int> const &src1, int v1) : SetsSupperPostion(src1, v1) {}
    ~SetsDifferState()
    {
        delete state1;
        delete state2;
    }
    bool contains(int s) const
    {
        return (state1->contains(s)) && (!state2->contains(s));
    }
};

class SetsIntersectState : public SetsSupperPostion
{
public:
    SetsIntersectState() : SetsSupperPostion() {}
    SetsIntersectState(State &st1, State &st2) : SetsSupperPostion(st1, st2) {}
    SetsIntersectState(int beg1, int end1, int beg2, int end2) : SetsSupperPostion(beg1, end1, beg2, end2) {}
    SetsIntersectState(int beg1, int end1, int v1) : SetsSupperPostion(beg1, end1, v1) {}
    SetsIntersectState(int beg1, int end1, std::set<int> const &src) : SetsSupperPostion(beg1, end1, src) {}
    SetsIntersectState(std::set<int> const &src1, std::set<int> const &src2) : SetsSupperPostion(src1, src2) {}
    SetsIntersectState(std::set<int> const &src1, int v1) : SetsSupperPostion(src1, v1) {}
    ~SetsIntersectState()
    {
        delete state1;
        delete state2;
    }
    bool contains(int s) const
    {
        return (state1->contains(s)) && (state2->contains(s));
    }
};

class SetsUnionState : public SetsSupperPostion
{
public:
    SetsUnionState() : SetsSupperPostion() {}
    SetsUnionState(State &st1, State &st2) : SetsSupperPostion(st1, st2) {}
    SetsUnionState(int beg1, int end1, int beg2, int end2) : SetsSupperPostion(beg1, end1, beg2, end2) {}
    SetsUnionState(int beg1, int end1, int v1) : SetsSupperPostion(beg1, end1, v1) {}
    SetsUnionState(int beg1, int end1, std::set<int> const &src) : SetsSupperPostion(beg1, end1, src) {}
    SetsUnionState(std::set<int> const &src1, std::set<int> const &src2) : SetsSupperPostion(src1, src2) {}
    SetsUnionState(std::set<int> const &src1, int v1) : SetsSupperPostion(src1, v1) {}
    ~SetsUnionState()
    {
        delete state1;
        delete state2;
    }
    bool contains(int s) const
    {
        return (state1->contains(s)) || (state2->contains(s));
    }
};

class ProbabilityTest
{
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count) : seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) {}
    ~ProbabilityTest() {}
    float operator()(State const &s) const
    {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min, test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng)))
                ++good;

        return static_cast<float>(good) / static_cast<float>(test_count);
    }
};

class Final : public SetsSupperPostion
{
    Final(int begin, int end, std::set<int> s1, std::set<int> s2)
    {
        state1 = new SegmentState(begin, end);
        state2 = new SetState(s1);
        State *temp = new SetState(s2);
        state1 = new SetsUnionState(*state1, *state2);
        state2 = new SetsDifferState(*state1, *temp);
    }
    bool contains(int s) const
    {
        return (state2->contains(s));
    }
};

int main(int argc, const char *argv[])
{
    int CountOfTests;

    std::mt19937 rng(std::random_device{}());

    std::ofstream outfile1;                      // declaration of file pointer named outfile
    outfile1.open("output1.txt", std::ios::out); // opens file named "filename" for output

    std::ofstream outfile2;                      // declaration of file pointer named outfile
    outfile2.open("output2.txt", std::ios::out); // opens file named "filename" for output

    std::ofstream outfile3;                      // declaration of file pointer named outfile
    outfile3.open("output3.txt", std::ios::out); // opens file named "filename" for output

    std::ofstream outfile4;                      // declaration of file pointer named outfile
    outfile4.open("output4.txt", std::ios::out); // opens file named "filename" for output

    std::ofstream outfile5;                      // declaration of file pointer named outfile
    outfile5.open("output5.txt", std::ios::out); // opens file named "filename" for output

    for (int j = 0; j < 100; ++j)
        for (int i = 0; i < 500; ++i)
        {
            CountOfTests = i;
            ProbabilityTest p(10, 0, 100, CountOfTests);

            {
                SegmentState *StateToTest = new SegmentState(0, j);
                outfile1 << p(*StateToTest) << '\n';
                delete StateToTest;
            }
            {
                std::set<int> s;
                for (int k = 0; k < j; ++k)
                {
                    if (std::uniform_int_distribution<>{0, 1}(rng))
                        s.insert(k);
                }
                SetState *StateToTest = new SetState(s);
                outfile2 << p(*StateToTest) << '\n';
                delete StateToTest;
            }
            {
                DiscreteState *StateToTest = new DiscreteState(std::uniform_int_distribution<>{0, 100}(rng));
                outfile3 << p(*StateToTest) << '\n';
                delete StateToTest;
            }
            {
                std::set<int> s;
                for (int k = 0; k < j; ++k)
                {
                    if (std::uniform_int_distribution<>{0, 1}(rng))
                        s.insert(k);
                }
                SetsUnionState *StateToTest = new SetsUnionState(0, j, s);

                outfile4 << p(*StateToTest) << '\n';
                delete StateToTest;
            }
            // SegmentState *StateToTest = new SegmentState(0, j);
            // outfile << p(*StateToTest) << '\n';
            // delete StateToTest;

            // SegmentState *StateToTest = new SegmentState(0, j);
            // outfile << p(*StateToTest) << '\n';
            // delete StateToTest;
            //  SegmentState StateToTest(0, j);
            //  SegmentState StateToTest(0, j);
            //  SegmentState StateToTest(0, j);

            // outfile << p(StateToTest) << '\n';
        }
    outfile1.close(); // closes file; always do this when you are done using the file
    outfile2.close(); // closes file; always do this when you are done using the file
    outfile3.close(); // closes file; always do this when you are done using the file
    outfile4.close(); // closes file; always do this when you are done using the file
    outfile5.close(); // closes file; always do this when you are done using the file

    // system("pause");
    std::cout << "good";
    return 0;
}
