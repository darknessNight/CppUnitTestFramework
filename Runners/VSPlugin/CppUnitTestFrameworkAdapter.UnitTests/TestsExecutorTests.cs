using NUnit.Framework;
using NSubstitute;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestPlatform.ObjectModel;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Adapter;

namespace darknessNight.CppUnitTest.VSAdapter.UnitTests {
    [TestFixture]
    public class TestsExecutorTests {
        [Test]
        public void TestRunTestFromTestCase_HasSampleTestCase_CheckRunTest() {
            List<TestResult> results = new List<TestResult>();
            actAndPrepareRunTestsFromTestCase(results);
            Assert.AreEqual(TestOutcome.Skipped, results[0].Outcome);
        }

        private static void actAndPrepareRunTestsFromTestCase(List<TestResult> results) {
            TestCase testCase = prepareSampleIgnoredTest();
            IFrameworkHandle framework = prepareFakeFrameworkToGetSendedResults(results);
            actRunTestsFromTestCaseArray(testCase, framework);
        }

        private static TestCase prepareSampleIgnoredTest() {
            return new TestCase("IgnoredMethod(ExampleProject::Tests::ClassTests)", TestDiscover.executorUri, IntegrationsPaths.getExampleTestPath());
        }

        private static IFrameworkHandle prepareFakeFrameworkToGetSendedResults(List<TestResult> results) {
            var framework = Substitute.For<IFrameworkHandle>();
            framework.RecordResult(Arg.Do<TestResult>((arg) => { results.Add(arg); }));
            return framework;
        }

        private static void actRunTestsFromTestCaseArray(TestCase testCase, IFrameworkHandle framework){
            TestsExecutor executor = new TestsExecutor();
            executor.RunTests(new[]{testCase}, null, framework);
        }

        [Test]
        public void TestRunTestFromSources_hasCorrectLibPath_CheckRunTest(){
            List<TestResult> results=new List<TestResult>();
            var framework = prepareFakeFrameworkToGetSendedResults(results);
            TestsExecutor executor=new TestsExecutor();
            executor.RunTests(new[]{"Path"},null,framework);

        }
    }
}
