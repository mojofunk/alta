#ifndef MOJO_CORE_DISALLOW_COPY_AND_ASSIGN_H
#define MOJO_CORE_DISALLOW_COPY_AND_ASSIGN_H

#define M_DISALLOW_COPY(TypeName) TypeName(const TypeName&) = delete

#define M_DISALLOW_ASSIGN(TypeName) void operator=(const TypeName&) = delete

#define M_DISALLOW_COPY_AND_ASSIGN(TypeName)                                   \
	TypeName(const TypeName&) = delete;                                           \
	void operator=(const TypeName&) = delete

#endif // MOJO_CORE_DISALLOW_COPY_AND_ASSIGN_H
