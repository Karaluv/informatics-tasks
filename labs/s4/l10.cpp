#include <iostream>
#include <set>
#include <random>
#include <vector>

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
public:
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
    DiscreteState d(1);
    SegmentState s(0, 10);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    SetsDifferState SD(ss, d);
    SetsIntersectState SI(0, 10, {1, 3, 5});
    SetsUnionState SU(SD, SI);
    ProbabilityTest pt(10, 0, 100, 100000);
    Final fin(0, 10, {1, 11, 12}, {0, 1, 3, 4, 5});
    std::cout << "State  Direct " << pt(d) << std::endl;
    std::cout << "State  Segment " << pt(s) << std::endl;
    std::cout << "State  Set " << pt(ss) << std::endl;
    std::cout << "State  Difference between third one and first " << pt(SD) << std::endl;
    std::cout << "State  Interception between (0,10) and {1 , 3 ,5} for example " << pt(SI) << std::endl;
    std::cout << "State  Union between 4th and 5th for example " << pt(SU) << std::endl;
    std::cout << "Final dop " << pt(fin) << std::endl;
    return 0;
}