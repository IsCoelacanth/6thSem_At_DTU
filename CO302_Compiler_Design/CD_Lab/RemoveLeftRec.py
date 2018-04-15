from functools import reduce

def main():
    num_prods = int(input("Enter the number of inputs : "))
    prods = []
    for i in range(num_prods):
        t_prod = input()
        t_prod = t_prod.split('->')
        t_prod = tuple(t_prod)
        prods.append(t_prod)
    print(prods)
    prod_d = {}
    print(prods)
    for pro in prods:
        if prod_d.get(pro[0]) is None:
            prod_d[pro[0]] = []
        prod_d[pro[0]].append(pro[1])

    new_prod = {}
    for NonT in prod_d:
        is_prod = reduce(lambda acc, new: new[0] == NonT or acc, prod_d[NonT], False)
        if is_prod:
            LR = list(filter(lambda new: new[0] == NonT, prod_d[NonT]))
            nonLR = list(filter(lambda new: new[0] != NonT, prod_d[NonT]))
            newP = "{}'".format(NonT)
            new_prod[newP] = ["$"]
            LR = list(map(lambda new: "{}{}".format(new[1:], newP), LR))
            print(LR)
            nonLR = list(map(lambda new: "{}{}".format(new, newP), nonLR))
            prod_d[NonT] = nonLR
            new_prod[newP].extend(LR)

    prod_d.update(new_prod)

    print("Productions are")
    for p in prod_d.items():
        print("{} -> {}".format(p[0], p[1]))
main()