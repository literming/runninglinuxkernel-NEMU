#ifndef __ISA_H__
#define __ISA_H__

// The macro `_ISA_H_` is defined in $(CFLAGS).
// It will be expanded as "isa/x86.h" or "isa/mips32.h" ...
#include _ISA_H_

// The macro `__ISA__` is defined in $(CFLAGS).
// It will be expanded as "x86" or "mips32" ...
typedef concat(__ISA__, _CPU_state) CPU_state;
typedef concat(__ISA__, _ISADecodeInfo) ISADecodeInfo;

// monitor
extern char isa_logo[];
void init_isa();

// reg
extern CPU_state cpu;
void isa_reg_display();
word_t isa_reg_str2val(const char *name, bool *success);

// exec
uint32_t isa_execute(uint32_t n);
void isa_hostcall(uint32_t id, rtlreg_t *dest, const rtlreg_t *src, uint32_t imm);

// memory
enum { MEM_TYPE_IFETCH, MEM_TYPE_READ, MEM_TYPE_WRITE };
enum { MEM_RET_OK, MEM_RET_NEED_TRANSLATE, MEM_RET_FAIL, MEM_RET_CROSS_PAGE };
paddr_t isa_mmu_translate(vaddr_t vaddr, int type, int len);
#ifndef isa_vaddr_check
int isa_vaddr_check(vaddr_t vaddr, int type, int len);
#endif

// exception and interrupt
#define isa_has_mem_exception concat(__ISA__, _has_mem_exception)
void isa_query_intr();

// difftest
  // for dut
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc);
void isa_difftest_attach();

  // for ref
void isa_difftest_regcpy(void *dut, bool direction);
void isa_difftest_raise_intr(word_t NO);

#endif
