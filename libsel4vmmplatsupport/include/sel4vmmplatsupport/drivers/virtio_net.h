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

/***
 * @module virtio_net.h
 * This interface provides the ability to initalise a VMM virtio net driver. This creating a virtio
 * PCI device in the VM's virtual pci. This can subsequently be accessed as an ethernet interface in the
 * guest.
 */

#include <sel4vm/guest_vm.h>

#include <sel4vmmplatsupport/ioports.h>
#include <sel4vmmplatsupport/drivers/pci.h>
#include <sel4vmmplatsupport/drivers/virtio_pci_emul.h>

/***
 * @struct virtio_net
 * Virtio Net Driver Interface
 * @param {unsigned int} iobase                         IO Port base for Virtio Net device
 * @param {virtio_emul_t *} emul                        Virtio Ethernet emulation interface: VMM <-> Guest
 * @param {struct eth_driver *} emul_driver             Backend Ethernet driver interface: VMM <-> Ethernet driver
 * @param {struct raw_iface_funcs} emul_driver_funcs    Virtio Ethernet emulation functions: VMM <-> Guest
 * @param {ps_io_ops_t} ioops                           Platform support ioops for dma management
 */
typedef struct virtio_net {
    unsigned int iobase;
    virtio_emul_t *emul;
    struct eth_driver *emul_driver;
    struct raw_iface_funcs emul_driver_funcs;
    ps_io_ops_t ioops;
} virtio_net_t;

/***
 * @function common_make_virtio_net(vm, pci, ioport, ioport_range, port_type, interrupt_pin, interrupt_line, backend, emulate_bar_access)
 * Initialise a new virtio_net device with Base Address Registers (BARs) starting at iobase and backend functions
 * specified by the raw_iface_funcs struct.
 * @param {vm_t *} vm                       A handle to the VM
 * @param {vmm_pci_space_t *} pci           PCI library instance to register virtio net device
 * @param {vmm_io_port_list_t *} ioport     IOPort library instance to register virtio net ioport
 * @param {ioport_range_t} ioport_range     BAR port for front end emulation
 * @param {ioport_type_t} port_type         Type of ioport i.e. whether to alloc or use given range
 * @param {unsigned int} interrupt_pin      PCI interrupt pin e.g. INTA = 1, INTB = 2 ,...
 * @param {unsigned int} interrupt_line     PCI interrupt line for virtio net IRQS
 * @param {struct raw_iface_funcs} backend  Function pointers to backend implementation. Can be initialised by
 *                                          virtio_net_default_backend for default methods.
 * @param {bool} emulate_bar                Emulate read and writes accesses to the PCI device Base Address Registers.
 * @return                                  Pointer to an initialised virtio_net_t, NULL if error.
 */
virtio_net_t *common_make_virtio_net(vm_t *vm, vmm_pci_space_t *pci, vmm_io_port_list_t *ioport,
                                     ioport_range_t ioport_range, ioport_type_t port_type, unsigned int interrupt_pin, unsigned int interrupt_line,
                                     struct raw_iface_funcs backend, bool emulate_bar_access);

/***
 * @function virtio_net_default_backend()
 * @return          A struct with a default virtio_net backend. It is the responsibility of the caller to
 *                  update these function pointers with its own custom backend.
 */
struct raw_iface_funcs virtio_net_default_backend(void);
