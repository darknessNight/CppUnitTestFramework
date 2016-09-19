using System;
using NUnit.Framework;
using NSubstitute;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestPlatform.ObjectModel;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Adapter;
using Microsoft.VisualStudio.TestPlatform.ObjectModel.Logging;


namespace darknessNight.CppUnitTest.VSAdapter.UnitTests {
    [TestFixture]
    public class TestsExecutorTests {
        [Test]
        public void RunTestFromTestCase_HasSampleTestCase_CheckRunTest(){
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
            return new TestCase("IgnoredMethod(ExampleProject::Tests::ClassTests)", new Uri("executor://exe"), IntegrationsPaths.getExampleTestPath());
        }

        private static IFrameworkHandle prepareFakeFrameworkToGetSendedResults(List<TestResult> results) {
            var framework = Substitute.For<IFrameworkHandle>();
            framework.RecordResult(Arg.Do<TestResult>((arg) => { results.Add(arg); }));
            return framework;
        }

        private static void actRunTestsFromTestCaseArray(TestCase testCase, IFrameworkHandle framework){
            TestExecutor executor = new TestExecutor();
            executor.RunTests(new[]{testCase}, null, framework);
        }

        [Test]
        public void RunTestFromSources_hasCorrectLibPath_CheckRunTest(){
            List<TestResult> results=new List<TestResult>();
            var framework = prepareFakeFrameworkToGetSendedResults(results);
            TestExecutor executor=new TestExecutor();
            executor.RunTests(new[]{ IntegrationsPaths.getExampleTestPath()},null,framework);
            Assert.IsTrue(results.Count>0);
        }

        [Test]
        public void RunTestFromSources_hasCorrectLibPath_CheckCreateLogs() {
            List<string> logs = new List<string>();
            var framework = Substitute.For<IFrameworkHandle>();
            framework.SendMessage(Arg.Any<TestMessageLevel>(), Arg.Do<string>(logs.Add));
            TestExecutor executor = new TestExecutor();
            executor.RunTests(new[] { IntegrationsPaths.getExampleTestPath() }, null, framework);
            AssertCreateLogs(logs);
        }

        private static void AssertCreateLogs(List<string> logs){
            CollectionAssert.Contains(logs, "Start running test:CppUnitTestAdapter");
            CollectionAssert.Contains(logs, "DiscoverStarted");
            CollectionAssert.Contains(logs, "DiscoverEnded");
            CollectionAssert.Contains(logs, "Loaded tests: 15");
            CollectionAssert.Contains(logs, "CppUnitTestAdapter: runned tests: 15");
        }
    }
}
