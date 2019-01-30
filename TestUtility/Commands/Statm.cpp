#include "../CommandCore/TestCommandController.h"
#include "../CommandCore/TestCommandBase.h"
#include "MemoryAllocation.h"

namespace WPEFramework {

class Statm : public TestCommandBase {
    private:
        Statm(const Statm&) = delete;
        Statm& operator=(const Statm&) = delete;

    public:
        Statm()
            : TestCommandBase(TestCommandBase::DescriptionBuilder("Provides information about system memory allocation"),
                              TestCommandBase::SignatureBuilder(TestCore::TestCommandSignature::Parameter("memory", "JSON", "memory statistics in KB")))
            , _memoryAdmin(MemoryAllocation::Instance())
        {
            TestCore::TestCommandController::Instance().Announce(this);
        }

        virtual ~Statm()
        {
            TestCore::TestCommandController::Instance().Revoke(this);
        }

    public:
        // ICommand methods
        string Execute(const string& params) final
        {
            return _memoryAdmin.CreateResponse();
        }

        string Name() const final
        {
            return _name;
        }

    private:
        BEGIN_INTERFACE_MAP(Statm)
            INTERFACE_ENTRY(Exchange::ITestUtility::ICommand)
        END_INTERFACE_MAP

    private:
        MemoryAllocation& _memoryAdmin;
        const string _name = _T("Statm");
};

static Statm* _singleton(Core::Service<Statm>::Create<Statm>());

} // namespace WPEFramework
