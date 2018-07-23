#ifndef RRT_STAR_HPP
#define RRT_STAR_HPP

#include <functional>

#include "motion_planning/Steer/Steer.hpp"
#include "motion_planning/Occupancy/Occupancy.hpp"

template <class State>
class RRTStar {
public:
    struct Node {
        State state;
        Node * parent;
        std::vector<Node *> children;
        double cost;
    };

private:
    Steer<State> * steer;
    const Occupancy<State> * occupancy;
    const std::function<State(void)> sampleState;
    const std::function<bool(const State *)> isGoal;

    std::vector<Node> nodes;
    std::vector<Node *> goalNodes;

    //void insert(const Node &node);
    Node * initNode(const State & state, Node * parent, double cost);

    std::vector<Node *> nearestNodes(const State * state);

    Node * growTree(const State & rand, const std::vector<Node*> & nearNodes);

    void rewire(Node * rand, const std::vector<Node*> & nearNodes);

public:
    /** 
     * Initialize the RRTStar algorithm.
     *
     * @param steer Determines feasible paths between states in free space.
     * @param occupancy Determines whether a state is in free space.
     * @param stateSampler Samples states in free space.
     * @param goalChecker Checks whether states are in the goal region.
     */
    RRTStar(
        Steer<State> * steer_, 
        const Occupancy<State> * occupancy_, 
        std::function<State(void)> sampleState_,
        std::function<bool(const State *)> isGoal_);

    /**
     * Perform one iteration of the RRTStar algorithm
     *
     * This generates a single random sample and attempts
     * to add it to the tree of paths.
     *
     * @returns True iff the random sample is added to the tree
     */
    bool iterate();

    std::vector<Node *> goals() {return goalNodes;};
};

#endif // RRT_STAR_HPP
