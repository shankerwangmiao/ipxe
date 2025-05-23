#ifndef _IPXE_FDT_H
#define _IPXE_FDT_H

/** @file
 *
 * Flattened Device Tree
 *
 */

FILE_LICENCE ( GPL2_OR_LATER_OR_UBDL );

#include <stdint.h>
#include <ipxe/image.h>

struct net_device;

/** Device tree header */
struct fdt_header {
	/** Magic signature */
	uint32_t magic;
	/** Total size of device tree */
	uint32_t totalsize;
	/** Offset to structure block */
	uint32_t off_dt_struct;
	/** Offset to strings block */
	uint32_t off_dt_strings;
	/** Offset to memory reservation block */
	uint32_t off_mem_rsvmap;
	/** Version of this data structure */
	uint32_t version;
	/** Lowest version to which this structure is compatible */
	uint32_t last_comp_version;
	/** Physical ID of the boot CPU */
	uint32_t boot_cpuid_phys;
	/** Length of string block */
	uint32_t size_dt_strings;
	/** Length of structure block */
	uint32_t size_dt_struct;
} __attribute__ (( packed ));

/** Magic signature */
#define FDT_MAGIC 0xd00dfeed

/** Expected device tree version */
#define FDT_VERSION 16

/** Device tree token */
typedef uint32_t fdt_token_t;

/** Begin node token */
#define FDT_BEGIN_NODE 0x00000001

/** End node token */
#define FDT_END_NODE 0x00000002

/** Property token */
#define FDT_PROP 0x00000003

/** Property fragment */
struct fdt_prop {
	/** Data length */
	uint32_t len;
	/** Name offset */
	uint32_t name_off;
} __attribute__ (( packed ));

/** NOP token */
#define FDT_NOP 0x00000004

/** End of structure block */
#define FDT_END 0x00000009

/** Alignment of structure block */
#define FDT_STRUCTURE_ALIGN ( sizeof ( fdt_token_t ) )

/** Maximum alignment of any block */
#define FDT_MAX_ALIGN 8

/** A device tree */
struct fdt {
	/** Tree data */
	union {
		/** Tree header */
		struct fdt_header *hdr;
		/** Raw data */
		void *raw;
	};
	/** Length of tree */
	size_t len;
	/** Used length of tree */
	size_t used;
	/** Offset to structure block */
	unsigned int structure;
	/** Length of structure block */
	size_t structure_len;
	/** Offset to strings block */
	unsigned int strings;
	/** Length of strings block */
	size_t strings_len;
	/** Offset to memory reservation block */
	unsigned int reservations;
	/** Reallocate device tree
	 *
	 * @v fdt		Device tree
	 * @v len		New length
	 * @ret rc		Return status code
	 */
	int ( * realloc ) ( struct fdt *fdt, size_t len );
};

extern struct image_tag fdt_image __image_tag;
extern struct fdt sysfdt;

extern int fdt_path ( struct fdt *fdt, const char *path,
		      unsigned int *offset );
extern int fdt_alias ( struct fdt *fdt, const char *name,
		       unsigned int *offset );
extern const char * fdt_string ( struct fdt *fdt, unsigned int offset,
				 const char *name );
extern int fdt_u64 ( struct fdt *fdt, unsigned int offset, const char *name,
		     uint64_t *value );
extern int fdt_mac ( struct fdt *fdt, unsigned int offset,
		     struct net_device *netdev );
extern int fdt_parse ( struct fdt *fdt, struct fdt_header *hdr,
		       size_t max_len );
extern int fdt_create ( struct fdt_header **hdr, const char *cmdline );
extern void fdt_remove ( struct fdt_header *hdr );

#endif /* _IPXE_FDT_H */
