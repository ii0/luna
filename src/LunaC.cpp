#include "State.h"
#include "VM.h"
#include "Bootstrap.h"
#include "Exception.h"
#include "BaseLib.h"
#include "StringLib.h"
#include <stdio.h>

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        printf("usage: %s file\n", argv[0]);
        return 0;
    }

    try
    {
        luna::State state;
        luna::VM vm(&state);
        luna::Bootstrap bootstrap(&state);

        lib::base::RegisterBaseLib(&state);
        lib::string::RegisterStringLib(&state);

        state.LoadModule(argv[1]);
        bootstrap.Prepare();
        vm.Execute();
    }
    catch (const luna::OpenFileFail &exp)
    {
        printf("%s: can not open file %s\n", argv[0], exp.What().c_str());
    }
    catch (const luna::Exception &exp)
    {
        printf("%s\n", exp.What().c_str());
    }

    return 0;
}
