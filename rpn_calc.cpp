#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include "stack.h"
#include "rpn_calc.h"

namespace rpn {

    using std::cout;
    using std::endl;
    using std::cerr;

    using std::pow;
    using std::sqrt;
    using std::log;
    using std::log2;
    using std::log10;
    using std::exp;
    using std::exp2;
    using std::sin;
    using std::cos;
    using std::tan;
    using std::asin;
    using std::acos;
    using std::atan;
    using std::atan2;
    using std::ceil;
    using std::floor;
    using std::fabs;


    token::token(const std::string &str, const std::unordered_map<std::string, long double> &variables) {
        if ((str.front() >= '0' && str.front() <= '9') || str.front() == '.') {
            type = NUMBER;
            number = std::stold(str);
        } else if (str == "pi" || str == "Pi" || str == "PI") {
            type = NUMBER;
            number = PI;
        } else if (str == "e") {
            type = NUMBER;
            number = e;
        } else if (str == "rand") {
            /*random number between 0 and 1*/
            type = NUMBER;
            number = std::rand() * 1.0L / RAND_MAX;
        } else if (variables.find(str) != variables.end()) {
            /*a variable*/
            type = NUMBER;
            number = variables.at(str);
        } else {
            type = OPERATOR;
            if (str == "+") {
                op = ADD;
            } else if (str == "-") {
                op = SUBTRACT;
            } else if (str == "*") {
                op = MULTIPLY;
            } else if (str == "/") {
                op = DIVIDE;
            } else if (str == "^2") {
                op = SQUARE;
            } else if (str == "sqrt") {
                op = SQRT;
            } else if (str == "^" || str == "pow") {
                op = POWER;
            } else if (str == "rt" || str == "root") {
                op = ROOT;
            } else if (str == "ln") {
                op = LOG_E;
            } else if (str == "log") {
                op = LOG_10;
            } else if (str == "lg") {
                op = LOG_2;
            } else if (str == "loga") {
                op = LOG_A;
            } else if (str == "exp") {
                op = EXP_E;
            } else if (str == "exp10") {
                op = EXP_10;
            } else if (str == "exp2") {
                op = EXP_2;
            } else if (str == "sin") {
                op = SIN_RAD;
            } else if (str == "cos") {
                op = COS_RAD;
            } else if (str == "tan") {
                op = TAN_RAD;
            } else if (str == "asin") {
                op = ASIN_RAD;
            } else if (str == "acos") {
                op = ACOS_RAD;
            } else if (str == "atan") {
                op = ATAN_RAD;
            } else if (str == "floor") {
                op = FLOOR;
            } else if (str == "ceil") {
                op = CEIL;
            } else if (str == "mod") {
                op = MODULO;
            } else {
                throw std::runtime_error("Invalid Token: " + str);
            }
        }
    }


    long double parse_rpn(const std::string &line, const std::unordered_map<std::string, long double> &variables) {
        containers::stack<token> stack(50);
        std::string word;
        std::stringstream stringstream(line);
        while (stringstream >> word) {
            token t(word, variables);
            if (t.type == OPERATOR) {
                switch (t.op) {
                    case ADD: {
                        long double ex1(stack.pop().number);
                        long double ex2(stack.pop().number);
                        stack.push(token(ex1 + ex2));
                        break;
                    }
                    case SUBTRACT: {
                        long double ex1(stack.pop().number);
                        long double ex2(stack.pop().number);
                        stack.push(token(ex2 - ex1));
                        break;
                    }
                    case MULTIPLY: {
                        long double ex1(stack.pop().number);
                        long double ex2(stack.pop().number);
                        stack.push(token(ex1 * ex2));
                        break;
                    }
                    case DIVIDE: {
                        long double ex1(stack.pop().number);
                        long double ex2(stack.pop().number);
                        stack.push(token(ex2 / ex1));
                        break;
                    }
                    case SQUARE: {
                        long double ex1(stack.pop().number);
                        stack.push(token(pow(ex1, 2)));
                        break;
                    }
                    case SQRT: {
                        long double ex1(stack.pop().number);
                        stack.push(token(sqrt(ex1)));
                        break;
                    }
                    case POWER: {
                        long double exp = stack.pop().number;
                        long double base = stack.pop().number;
                        stack.push(token(pow(base, exp)));
                        break;
                    }
                    case ROOT: {
                        long double exp = stack.pop().number;
                        long double base = stack.pop().number;
                        stack.push(token(pow(base, 1 / exp)));
                        break;
                    }
                    case LOG_E: {
                        long double ex1(stack.pop().number);
                        stack.push(token(log(ex1)));
                        break;
                    }
                    case LOG_10: {
                        long double ex1(stack.pop().number);
                        stack.push(token(log10(ex1)));
                        break;
                    }
                    case LOG_2: {
                        long double ex1(stack.pop().number);
                        stack.push(token(log2(ex1)));
                        break;
                    }
                    case LOG_A: {
                        long double base(stack.pop().number);
                        long double ex1(stack.pop().number);
                        stack.push(token(log2(ex1) / log2(base)));
                        break;
                    }
                    case EXP_E: {
                        long double ex1(stack.pop().number);
                        stack.push(token(exp(ex1)));
                        break;
                    }
                    case EXP_10: {
                        long double ex1(stack.pop().number);
                        stack.push(token(pow(10, ex1)));
                        break;
                    }
                    case EXP_2: {
                        long double ex1(stack.pop().number);
                        stack.push(token(exp2(ex1)));
                        break;
                    }
                    case SIN_RAD: {
                        long double ex1(stack.pop().number);
                        stack.push(token(sin(ex1)));
                        break;
                    }
                    case COS_RAD: {
                        long double ex1(stack.pop().number);
                        stack.push(token(cos(ex1)));
                        break;
                    }
                    case TAN_RAD: {
                        long double ex1(stack.pop().number);
                        stack.push(token(tan(ex1)));
                        break;
                    }
                    case ASIN_RAD: {
                        long double ex1(stack.pop().number);
                        stack.push(token(asin(ex1)));
                        break;
                    }
                    case ACOS_RAD: {
                        long double ex1(stack.pop().number);
                        stack.push(token(acos(ex1)));
                        break;
                    }
                    case ATAN_RAD: {
                        long double ex1(stack.pop().number);
                        stack.push(token(atan(ex1)));
                        break;
                    }
                    case ATAN2_RAD: {
                        long double ex2(stack.pop().number);
                        long double ex1(stack.pop().number);
                        stack.push(token(atan2(ex1, ex2)));
                        break;
                    }
                    case FLOOR: {
                        long double ex1(stack.pop().number);
                        stack.push(token(floor(ex1)));
                        break;
                    }
                    case CEIL: {
                        long double ex1(stack.pop().number);
                        stack.push(token(ceil(ex1)));
                        break;
                    }
                    case MODULO: {
                        long double ex1(stack.pop().number);
                        long double ex2(stack.pop().number);
                        stack.push(token(std::fmod(ex2, ex1)));
                        break;
                    }
                    default:
                        cerr << endl;
                        cerr << word << endl;
                        cerr << t.type << endl;
                        cerr << t.number << endl;
                        cerr << t.op << endl;
                        throw std::runtime_error("Invalid Token");
                }
            } else {
                stack.push(t);
            }
        }
        return stack.pop().number;
    }

    std::vector<token> tokenize_expression(const std::string &line) {
        std::vector<token> stack;
        const std::unordered_map<std::string, long double> variables;
        std::string word;
        std::stringstream stringstream(line);
        while (stringstream >> word) {
            token t(word, variables);
            stack.push_back(t);
        }
        return stack;
    }

    const std::string get_op_string(operator_type op) {
        switch (op) {
            case ADD:
                return "+";
            case SUBTRACT:
                return "-";
            case MULTIPLY:
                return "*";
            case DIVIDE:
                return "/";
            case SQUARE:
                return "^2";
            case SQRT:
                return "sqrt";
            case POWER:
                return "pow";
            case ROOT:
                return "root";
            case LOG_E:
                return "ln";
            case LOG_10:
                return "log";
            case LOG_2:
                return "lg";
            case LOG_A:
                return "loga";
            case EXP_E:
                return "exp";
            case EXP_10:
                return "exp10";
            case EXP_2:
                return "exp2";
            case SIN_RAD:
                return "sin";
            case COS_RAD:
                return "cos";
            case TAN_RAD:
                return "tan";
            case ASIN_RAD:
                return "asin";
            case ACOS_RAD:
                return "acos";
            case ATAN_RAD:
                return "atan";
            case FLOOR:
                return "floor";
            case CEIL:
                return "ceil";
            case MODULO:
                return "mod";
            default:
                return "ERROR";
        }
    }
}
