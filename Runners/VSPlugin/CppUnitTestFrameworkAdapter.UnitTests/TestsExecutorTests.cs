using NUnit.Framework;
using NSubstitute;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestPlatform;
using Microsoft.VisualStudio.TestPlatform.ObjectModel;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Adapter;

namespace darknessNight.CppUnitTest.VSAdapter.UnitTests {
    [TestFixture]
    public class TestsExecutorTests {
        [Test]
        public void TestRunTestFromTestCase_HasSampleTestCase_CheckRunTest() {
            List<TestResult> results = new List<TestResult>();
            TestCase testCase = new TestCase("IgnoredMethod(ExampleProject::Tests::ClassTests)", TestDiscover.executorUri, IntegrationsPaths.getExampleTestPath());
            TestsExecutor executor=new TestsExecutor();
            var framework = Substitute.For<IFrameworkHandle>();
            framework.RecordResult(Arg.Do<TestResult>((arg) => { results.Add(arg); }));
            executor.RunTests(new TestCase[] { testCase }, null,framework);
            Assert.AreEqual(TestOutcome.Skipped, results[0].Outcome);
        }
    }
}
