export module observer;

import resourcelist;

export class Observer {
    public:
        // The parameter lets us pass the necessary information
        // while avoiding the circular dependency from passing a Subject
        virtual void notify(ResourceList *resList) = 0;
        virtual ~Observer() = default;
};
