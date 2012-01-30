/*
 * InferenceTests.cpp
 *
 *  Created on: 30 janv. 2012
 *      Author: vincent
 */

#include "tests.h"

void InferenceTestsSimple(Test *test)
{
	InferenceActions actions;
	InferenceEngine eng("monitoring/tests/simple.xml");

	actions = eng.run(2, 20);
	test->assert(actions.size() == 0, "Metric to match is ok.");

	actions = eng.run(1, 15);
	test->assert(actions.size() == 0, "Value to match is ok.");

	actions = eng.run(1, 20);
	test->assert(actions.size() == 1, "Matching condition is taken in account.");
	if (actions.size() == 1)
	{
		test->assert(actions[0].getMetric() == 2, "Metric to apply is ok.");
		test->assert(actions[0].getValue() == 1, "Value to apply is ok.");
	}
}

void InferenceTestsMultipleActions(Test *test)
{
	InferenceActions actions;
	InferenceEngine eng("monitoring/tests/multipleActions.xml");

	actions = eng.run(1, 20);
	test->assert(actions.size() == 2, "All actions are returned.");
	if (actions.size() == 2)
	{
		test->assert(actions[0].getMetric() == 2 && actions[0].getValue() == 1, "Action 1 is ok.");
		test->assert(actions[1].getMetric() == 3 && actions[1].getValue() == 42, "Action 2 is ok.");
	}
}

void InferenceTestsMultipleConditions(Test *test)
{
	InferenceActions actions;
	InferenceEngine eng("monitoring/tests/multipleConditions.xml");

	actions = eng.run(1, 20);
	test->assert(actions.size() == 0, "With one matching metric, rule does not match.");

	actions = eng.run(3, 50);
	test->assert(actions.size() == 1, "With the second matching metric, rule matches.");
}


void InferenceTests(Test *test)
{
	test->add(&InferenceTestsSimple, "InferenceSimple");
	test->add(&InferenceTestsMultipleActions, "InferenceMultipleActions");
	test->add(&InferenceTestsMultipleConditions, "InferenceMultipleConditions");
}