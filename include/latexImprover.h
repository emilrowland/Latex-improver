#ifndef LATEXIMPROVER_H
#define LATEXIMPROVER_H

#include <sstream>
#include <string>
#include <vector>

class latexImprover{
    public:
        latexImprover(std::stringstream& file, std::stringstream& output);
    protected:
        struct ReplaceInstruction{
            int pos;
            std::string replacment;
            bool active = false;
        };
        std::vector<ReplaceInstruction*> preFormater(std::stringstream& file);
        void formater(std::stringstream& file, std::stringstream& output, std::vector<ReplaceInstruction*> instructions);
    private:
        bool inEnviromentAlign = false;
        bool inEnviromentEquation = false;
        bool inSimpelEquation = false;
        bool inShortEquation = false;
        bool inLabel = false;
        bool usePackageAmsmath = false;
        bool shouldBeActive = false;
        bool activeInst(bool stackEmpty, bool poped = true);
};

#endif // LATEXIMPROVER_H
