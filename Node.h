//Node.h
#ifndef NODE_H
#define NODE_H

#include "Patient.h"

class Node {
public:
    Patient data;
    Node* next;

    Node(const Patient& p);
};

#endif
