/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#pragma once

struct guest_kernel_image_arch {
    /* Enable kernel image relocation */
    bool is_reloc_enabled;
    /* Guest image relocation file */
    const char *relocs_file;
    /* Entry point for when the VM starts */
    uintptr_t entry;
    /* If we are loading a guest elf then we may not have been able to put it where it
     * requested. This is the relocation offset */
    int relocation_offset;
    /* Base physical address the image was linked for */
    uintptr_t link_paddr;
    uintptr_t link_vaddr;
};
