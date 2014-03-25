#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <climits>
#include <cfloat>
#include <cmath>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <limits>
#include <assert.h>

using namespace std;

#define DBG 0

#if DBG
#define D(x) x;
#else
#define D(x)
#endif

#define CLR(x, n) memset(x, 0, n*sizeof x[0]);

const int maxn = 15005;
const int maxr = 15005;

typedef int Num;
const Num INFM = numeric_limits<Num>::min();
const Num INFP = numeric_limits<Num>::max();

enum Oper {
	EQ,  //0
	NEQ, //1
	GT,  //2
	GTEQ,//3
	LT,  //4
	LTEQ,//5
	AND, //6
	OR,  //7
	NOP, //8
	CTRUE,//9
	CFALSE,//10
	OPER_MAX,
};

string opanme[] = {
		"==", "!=", ">", ">=", "<", "<=", "&&", "||", "*", "T", "F"
};

Oper parseOp(string &op) {
	if (!op.compare("=="))
		return EQ;
	else if (!op.compare("!="))
		return NEQ;
	else if (!op.compare(">"))
		return GT;
	else if (!op.compare(">="))
		return GTEQ;
	else if (!op.compare("<"))
		return LT;
	else if (!op.compare("<="))
		return LTEQ;
	else if (!op.compare("&&"))
		return AND;
	else if (!op.compare("||"))
		return OR;
	return NOP;
}

struct Expression {
	unsigned char var;
	Oper op;
	string val;

	Expression(Expression &e) : val() {
		var = e.var;
		op = e.op;
		val = e.val;
	}

	Expression(unsigned char v = 0, Oper o = NOP, string s = "0") : val (s) {
		assert( o < OPER_MAX );
		var = v;
		op = o;
	}

	Expression &operator =(const Expression &e) {
		var = e.var;
		op = e.op;
		val = e.val;
		return *this;
	}

	Expression (istream &is) : val() {
		string sop;
		is >> var >> sop >> val;
		op = parseOp(sop);
	}

	void getRanges(Num &lo1, bool &lo1i, Num &hi1, bool &hi1i, bool &has2,
			Num &lo2, bool &lo2i, Num &hi2, bool &hi2i) {
		istringstream is(val);
		Num nval; is >> nval;

		switch (op) {
		case EQ:
			lo1 = hi1 = nval;
			lo1i = hi1i = true;
			has2 = false;
			break;
		case NEQ:
			lo1 = INFM; lo1i = hi2i = false;
			lo2 = hi1 = nval; hi1i = lo2i = false;
			hi2 = INFP;
			has2 = true;
			break;
		case GT:
			lo1 = nval; lo1i = hi1i = false;
			hi1 = INFP;
			has2 = false;
			break;
		case GTEQ:
			lo1 = nval; lo1i = true;
			hi1 = INFP; hi1i = false;
			has2 = false;
			break;
		case LT:
			lo1 = INFM; lo1i = hi1i = false;
			hi1 = nval;
			has2 = false;
			break;
		case LTEQ:
			lo1 = INFM; lo1i = false;
			hi1 = nval; hi1i = true;
			has2 = false;
			break;
		case CTRUE:
			lo1 = INFM; lo2 = INFP;
			lo1i = lo2i = false;
			has2 = false;
			break;
		case CFALSE:
			lo1 = lo2 = 0;
			lo1i = lo2i = false;
			has2 = false;
			break;
		default:
			break;
		}
	}

	bool intersect(Num lo1, bool lo1i, Num hi1, bool hi1i,
			Num lo2, bool lo2i, Num hi2, bool hi2i) {
		bool disj = hi1 < lo2 || (hi1 <= lo2 && (!hi1i || !lo2i));
		disj |= hi2 < lo1 || (hi2 <= lo1 && (!hi2i || !lo1i));
		return !disj;
	}

	bool intersect(Expression &e) {
		if (e.var != var) {
			// TODO test var is empty set
			return e.op != CFALSE && op != CFALSE;
		}

		Num Alo1; bool Alo1i; Num Ahi1; bool Ahi1i; bool Ahas2;
		Num Alo2; bool Alo2i; Num Ahi2; bool Ahi2i;

		Num Blo1; bool Blo1i; Num Bhi1; bool Bhi1i; bool Bhas2;
		Num Blo2; bool Blo2i; Num Bhi2; bool Bhi2i;

		getRanges(Alo1, Alo1i, Ahi1, Ahi1i, Ahas2, Alo2, Alo2i, Ahi2, Ahi2i);
		e.getRanges(Blo1, Blo1i, Bhi1, Bhi1i, Bhas2, Blo2, Blo2i, Bhi2, Bhi2i);

		bool inte = intersect(Alo1, Alo1i, Ahi1, Ahi1i, Blo1, Blo1i, Bhi1, Bhi1i) /* A1 B1 */ ||
				(Ahas2 && intersect(Alo2, Alo2i, Ahi2, Ahi2i, Blo1, Blo1i, Bhi1, Bhi1i)) /* A2 B1 */;
		inte |= Bhas2 && intersect(Alo1, Alo1i, Ahi1, Ahi1i, Blo2, Blo2i, Bhi2, Bhi2i); /* A1 B2 */
		inte |= Ahas2 && Bhas2 && intersect(Alo2, Alo2i, Ahi2, Ahi2i, Blo2, Blo2i, Bhi2, Bhi2i); /* A2 B2 */

		return inte;
	}
};

ostream& operator<<(ostream &os, Expression &e) {
	return os << e.var << " " << opanme[e.op] << " " << e.val;
}

struct Node {
	Expression expr;
	int left, right;
	int parent;
	Node() {
		left = right = 0;
		parent = -1;
	}
	Node(Expression &_expr) {
		expr = _expr;
		left = right = 0;
		parent = -1;
	}
};

ostream& operator<<(ostream &os, Node &nd) {
	return os << nd.expr << " left " << nd.left << " right " << nd.right << " parent " << nd.parent << endl;
}

//// VAR

int n, r, i;
string strE;

Node tree[maxn];
Expression e1,e2;
Oper eop;

// keep path expressions here
#define MAXVAR 256
vector<list<string> > neqVals(MAXVAR,list<string>());	// NEQ values in path
Expression pex[MAXVAR][OPER_MAX];	// path expression for e1.var and e2.var
bool pexv[MAXVAR][OPER_MAX];		// path expression is in use

void parseE(string &s) {
	istringstream is(s);
	e1 = Expression(is);
	
	string andor;
	if (is >>andor) {
		eop = parseOp(andor);
		e2 = Expression(is);
	} else {
		e2.var = 0;
		eop = NOP;
	}
}

Oper swapop(Oper op) {
	switch (op) {
	case LT:
		return GT;
	case LTEQ:
		return GTEQ;
	case GT:
		return LT;
	case GTEQ:
		return LTEQ;
	default:
		break;
	}
	return op;
}

Oper constantop(Num l, Num r, Oper op)
{
	bool res;
	switch (op) {
	case EQ:
		res = l == r;
		break;
	case NEQ:
		res = l != r;
		break;
	case GT:
		res = l > r;
		break;
	case GTEQ:
		res = l >= r;
		break;
	case LT:
		res = l < r;
		break;
	case LTEQ:
		res = l <= r;
		break;
	default:
		res = false;
		break;
	}

	return res ? CTRUE : CFALSE;
}

void dump(ostream &os) {
	int i;
	for (i=0;i<n;i++)
		cout<<"#"<<i<<" "<<tree[i];
}

bool pathmatch(Expression &ex) {
	for (int op = EQ; op <= LTEQ; op++) {
		if (pexv[ex.var][op]) {
			if (op == NEQ) {
				Expression neq(ex.var, NEQ);
				for (list<string>::iterator it = neqVals[ex.var].begin();
						it != neqVals[ex.var].end(); it++) {
					neq.val = *it;
					if (!neq.intersect(ex))
						return false; // CHECK (why not just compare == ?)
				}
			} else {
				if (!ex.intersect(pex[ex.var][op]))
					return false;
			}
		}
	}
	return true;
}

bool satisfy(Expression &ex) {
	bool pok = pathmatch(ex);
	bool ok1 = pok && ex.intersect(e1);
	bool ok2;

	if (eop == AND) {
		ok2 = pok && ex.intersect(e2);
		return ok1 && ok2;
	} else if (eop == OR) {
		ok2 = pok && ex.intersect(e2);
		return pok && (ok1 || ok2);
	} else
		return ok1;
}

void updatePath(Expression &ex) {
	if (ex.op == NEQ) {
		// special case
		neqVals[ex.var].push_back(ex.val);
	}

	if (!pexv[ex.var][ex.op]) {
		pexv[ex.var][ex.op] = 1;
		pex[ex.var][ex.op] = ex;
	} else {
		switch (ex.op) {
		case EQ:
			if (ex.val != pex[ex.var][ex.op].val)
				pex[ex.var][ex.op].val = INFM; // impossible val
			break;
		case GT:
			pex[ex.var][ex.op].val = max(pex[ex.var][ex.op].val, ex.val);
			break;
		case GTEQ:
			pex[ex.var][ex.op].val = max(pex[ex.var][ex.op].val, ex.val);
			break;
		case LT:
			pex[ex.var][ex.op].val = min(pex[ex.var][ex.op].val, ex.val);
			break;
		case LTEQ:
			pex[ex.var][ex.op].val = min(pex[ex.var][ex.op].val, ex.val);
			break;
		default:
			break;
		}
	}
}

int findPCNode(int u) {
	Node &node=tree[u];

	// cut
	bool pctrue = satisfy(node.expr);
	if (!pctrue)
		return -1;

	// base case: found pc leaf
	if (!node.left && !node.right)
		return u;

	// save path expr
	bool oldV = pexv[node.expr.var][node.expr.op];
	Expression old = pex[node.expr.var][node.expr.op];
	
	// update path
	updatePath(node.expr);
	
	int rc = -1, v;
	if (node.left && (v = findPCNode(node.left)) > 0) {
		rc = v;
		goto exit;
	}
		
	if (node.right && (v = findPCNode(node.right)) > 0) {
		rc = v;
		goto exit;
	}
	
exit:
	// restore path
	pexv[node.expr.var][node.expr.op] = oldV;
	pex[node.expr.var][node.expr.op] = old;

	if (node.expr.op == NEQ) // pop neq value
		neqVals[node.expr.var].pop_back();

	return rc;
}

Num toNum(string &s) {
	Num n;
	istringstream is(s);
	is >> n;
	return n;
}

string toStr(Num n) {
	ostringstream os;
	os << n;
	return os.str();
}

int main() {
	int T;
	string line;
	int nodeNum,childNum,child1,child2;

#if BENCH
	freopen("defect_detect.txt","r",stdin);
#endif

	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		getline(cin,strE);
		if (strE.empty())
			getline(cin,strE);

		parseE(strE);

		cin >> n >> r; getline(cin, line);

		for (i=0;i<n;i++) {
			getline(cin, line);
			istringstream is(line);
			string lhs;
			is >> nodeNum >> lhs;

			if (lhs[0] == 'R') {
				// root node
				tree[nodeNum].expr = Expression(lhs[0], NOP);
			} else {
				// expression
				string ops;
				string rhs;
				is >> ops;
				is >> rhs;

				Oper op = parseOp(ops);
				// regularize (lhs = var name, constants ==> CTRUE / CFALSE)
				if (isdigit(lhs[0]) || lhs[0] == '-') {
					if (isdigit(rhs[0]) || rhs[0] == '-') {
						// special constant case
						op = constantop(toNum(lhs), toNum(rhs), op);
					} else {
						swap(lhs, rhs);
						op = swapop(op);
					}
				}

				tree[nodeNum].expr = Expression((unsigned char)lhs[0], op, rhs);
			}
		}

		for (i=0;i<r;i++) {
			getline(cin,line);
			istringstream is(line);
			is>>nodeNum>>childNum;
			tree[nodeNum].left = tree[nodeNum].right = 0;
			if (childNum>=1) {
				is>>child1;
				tree[nodeNum].left=child1;
				tree[child1].parent=nodeNum;
			}
			if (childNum>=2) {
				is>>child2;
				tree[nodeNum].right=child2;
				tree[child2].parent=nodeNum;
			}
		}

		D(dump(cout));

		for (i=0;i<MAXVAR;i++)
			neqVals[i].clear();

		memset(pexv, 0, sizeof pexv);
		
		int ans = findPCNode(0);

		cout << "Case #" << tc + 1 << endl;
		cout << ans << endl;
	}

	return 0;
}
