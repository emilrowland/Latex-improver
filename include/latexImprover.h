#ifndef LATEXIMPROVER_H
#define LATEXIMPROVER_H

#include <sstream>

class latexImprover{
    public:
        latexImprover(std::stringstream& file, std::stringstream& output);
    protected:
    private:
        bool inEnviromentAlign = false;
};

#endif // LATEXIMPROVER_H
