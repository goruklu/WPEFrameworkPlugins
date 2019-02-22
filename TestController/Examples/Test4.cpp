#include "../Module.h"

#include "../Core/TestBase.h"
#include "../Core/Trace.h"
#include <interfaces/ITestController.h>
#include "TestCategory2.h"

namespace WPEFramework {

class Test4 : public TestBase {
    public:
        Test4(const Test4&) = delete;
        Test4& operator=(const Test4&) = delete;

        Test4()
            : TestBase(TestBase::DescriptionBuilder("Test 4 description"))
        {
            TestCore::TestCategory2::Instance().Register(this);;
        }

        virtual ~Test4()
        {
            TestCore::TestCategory2::Instance().Unregister(this);
        }

    public:
        // ICommand methods
        string Execute(const string& params) final
        {
            TestCore::TestResult jsonResult;
            string result;
            TRACE(TestCore::TestStart, (_T("Start execute of test: %s"), _name.c_str()));

            TRACE(TestCore::TestStep, (_T("Do real test execution"), _name.c_str()));
            jsonResult.Name = _name;
            jsonResult.OverallStatus = "Success";

            TRACE(TestCore::TestStart, (_T("End test: %s"), _name.c_str()));
            jsonResult.ToString(result);
            return result;
        }

        string Name() const final
        {
            return _name;
        }

    private:
        const string _name = _T("Test4");
};

static Exchange::ITestController::ITest* _singleton(Core::Service<Test4>::Create<Exchange::ITestController::ITest>());
} // namespace WPEFramework
