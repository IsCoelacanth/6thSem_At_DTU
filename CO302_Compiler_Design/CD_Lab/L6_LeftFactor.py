from functools import reduce
def left_factor(GRAMMAR):
    new_d = {}
    flag = False
    for nont in GRAMMAR:
        matches = []
        for sent in GRAMMAR[nont]:
            matches = list(filter(lambda x: x[0] == sent[0], GRAMMAR[nont]))
            if matches.__len__() > 1:
                break
        if matches.__len__() > 1:
            prefix = get_common_prefix(matches)
            new_d["{}`".format(nont)] = list(map(lambda x: x[len(prefix):], matches))
            new_d[nont] = list(filter(lambda x: x not in matches, GRAMMAR[nont])) + ["{}{}`".format(prefix, nont)]
            flag = True
            break
    if flag:
        for x in new_d:
            GRAMMAR[x] = new_d[x]
        return left_factor(GRAMMAR)
    return GRAMMAR

def common_perf(string1, string2):
    ans = []
    for x in zip(string1, string2):
        if x[0] == x[1]:
            ans.append(x[0])
        else:
            return ''.join(ans)
    return ''.join(ans)

def get_common_prefix(strings):
    return reduce(lambda prefix, x: common_perf(prefix, x), strings[1:], strings[0])

def main():
    n = int(input('Enter number of prductions as A->x|y|z : '))
    prods = []
    for i in range(n):
        prd = input().split('->')
        nt = prd[0]
        rhs = prd[1]
        rhs = rhs.split('|')
        for i in rhs:
            prods.append((nt,i))
        # print(prods)
    prodd = {}
    for x in prods :
        prodd[x[0]] = [x[1]] + prodd.get(x[0], [])
    
    print('Left factored grammar : ')
    lft = left_factor(prodd)
    for k in lft.keys():
        print(k, '->',lft[k])
main()