#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

void InfixToPostfix(const char* infix, char* postfix);
double calculator(char* postfix);

#endif // EXPRESSION_EVALUATOR_H
