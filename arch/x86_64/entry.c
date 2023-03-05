typedef unsigned long long uint64_t;
typedef uint64_t pml4e_t;
typedef uint64_t pdpte_t;
typedef uint64_t pde_t;

__attribute__((__aligned__(1 << 12)))
__attribute__((section(".bsdata")))
pml4e_t pml4e[512];

__attribute__((section(".bsdata")))
pdpte_t pdpte[512];

__attribute__((section(".bsdata")))
pde_t pde[512];

pml4e_t pml4e[512] = {
    [0] = (uint64_t)pdpte + 7,
};

pdpte_t pdpte[512] = {
    [0] = (uint64_t)pde + 3,
};

pde_t pde[512] = {
    [0] = 0x000083,
    [1] = 0x200083,
    [2] = 0x400083,
    [3] = 0x600083,
    [4] = 0x800083,
};
