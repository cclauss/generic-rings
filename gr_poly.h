#ifndef GR_POLY_H
#define GR_POLY_H

#ifdef GR_POLY_INLINES_C
#define GR_POLY_INLINE FLINT_DLL
#else
#define GR_POLY_INLINE static __inline__
#endif

#include "flint/fmpz_poly.h"
#include "gr.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* fixme: compatible with flint polys but not with arb, ... */
typedef struct
{
    gr_ptr coeffs;
    slong alloc;
    slong length;
}
gr_poly_struct;

typedef gr_poly_struct gr_poly_t[1];

void gr_poly_init(gr_poly_t poly, gr_ctx_t ctx);
void gr_poly_init2(gr_poly_t poly, slong len, gr_ctx_t ctx);
void gr_poly_clear(gr_poly_t poly, gr_ctx_t ctx);

GR_POLY_INLINE gr_ptr
gr_poly_entry_ptr(gr_poly_t poly, slong i, gr_ctx_t ctx)
{
    return GR_ENTRY(poly->coeffs, i, ctx->sizeof_elem);
}

GR_POLY_INLINE slong gr_poly_length(const gr_poly_t poly, gr_ctx_t ctx)
{
    return poly->length;
}

GR_POLY_INLINE void
gr_poly_swap(gr_poly_t poly1, gr_poly_t poly2, gr_ctx_t ctx)
{
    gr_poly_struct t = *poly1;
    *poly1 = *poly2;
    *poly2 = t;
}

void gr_poly_fit_length(gr_poly_t poly, slong len, gr_ctx_t ctx);
void _gr_poly_set_length(gr_poly_t poly, slong len, gr_ctx_t ctx);
void _gr_poly_normalise(gr_poly_t poly, gr_ctx_t ctx);

WARN_UNUSED_RESULT int gr_poly_set(gr_poly_t res, const gr_poly_t src, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_reverse(gr_ptr res, gr_srcptr poly, slong len, slong n, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_reverse(gr_poly_t res, const gr_poly_t poly, slong n, gr_ctx_t ctx);

GR_POLY_INLINE WARN_UNUSED_RESULT int
gr_poly_zero(gr_poly_t poly, gr_ctx_t ctx)
{
    _gr_poly_set_length(poly, 0, ctx);
    return GR_SUCCESS;
}

WARN_UNUSED_RESULT int gr_poly_one(gr_poly_t poly, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_neg_one(gr_poly_t poly, gr_ctx_t ctx);

int gr_poly_write(gr_stream_t out, const gr_poly_t poly, gr_ctx_t ctx);
int gr_poly_print(const gr_poly_t poly, gr_ctx_t ctx);

int gr_poly_randtest(gr_poly_t poly, flint_rand_t state, slong len, gr_ctx_t ctx);

truth_t _gr_poly_equal(gr_srcptr poly1, slong len1, gr_srcptr poly2, slong len2, gr_ctx_t ctx);
truth_t gr_poly_equal(const gr_poly_t poly1, const gr_poly_t poly2, gr_ctx_t ctx);

truth_t gr_poly_is_zero(const gr_poly_t poly, gr_ctx_t ctx);
truth_t gr_poly_is_one(const gr_poly_t poly, gr_ctx_t ctx);

WARN_UNUSED_RESULT int gr_poly_set_scalar(gr_poly_t poly, gr_srcptr x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_si(gr_poly_t poly, slong x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_ui(gr_poly_t poly, slong x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_fmpz(gr_poly_t poly, const fmpz_t x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_fmpq(gr_poly_t poly, const fmpq_t x, gr_ctx_t ctx);

/* todo: document/test */
WARN_UNUSED_RESULT int gr_poly_get_fmpz_poly(gr_poly_t res, const fmpz_poly_t src, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_fmpq_poly(gr_poly_t res, const fmpq_poly_t src, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_gr_poly_other(gr_poly_t res, const gr_poly_t x, gr_ctx_t x_ctx, gr_ctx_t ctx);

WARN_UNUSED_RESULT int gr_poly_set_coeff_scalar(gr_poly_t poly, slong n, gr_srcptr x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_coeff_si(gr_poly_t poly, slong n, slong x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_coeff_ui(gr_poly_t poly, slong n, ulong x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_coeff_fmpz(gr_poly_t poly, slong n, const fmpz_t x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_set_coeff_fmpq(gr_poly_t poly, slong n, const fmpq_t x, gr_ctx_t ctx);

WARN_UNUSED_RESULT int gr_poly_get_coeff_scalar(gr_ptr res, const gr_poly_t poly, slong n, gr_ctx_t ctx);

WARN_UNUSED_RESULT int gr_poly_neg(gr_poly_t res, const gr_poly_t src, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_add(gr_ptr res, gr_srcptr poly1, slong len1, gr_srcptr poly2, slong len2, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_add(gr_poly_t res, const gr_poly_t poly1, const gr_poly_t poly2, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_sub(gr_ptr res, gr_srcptr poly1, slong len1, gr_srcptr poly2, slong len2, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_sub(gr_poly_t res, const gr_poly_t poly1, const gr_poly_t poly2, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_mul(gr_ptr res, gr_srcptr poly1, slong len1, gr_srcptr poly2, slong len2, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_mul(gr_poly_t res, const gr_poly_t poly1, const gr_poly_t poly2, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_mullow_generic(gr_ptr res, gr_srcptr poly1, slong len1, gr_srcptr poly2, slong len2, slong n, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_mullow(gr_poly_t res, const gr_poly_t poly1, const gr_poly_t poly2, slong n, gr_ctx_t ctx);

WARN_UNUSED_RESULT int gr_poly_mul_scalar(gr_poly_t res, const gr_poly_t poly, gr_srcptr c, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_divrem_basecase_preinv(gr_ptr Q, gr_ptr R, gr_srcptr A, slong lenA, gr_srcptr B, slong lenB, gr_srcptr invB, gr_ctx_t ctx);
WARN_UNUSED_RESULT int _gr_poly_divrem_basecase_noinv(gr_ptr Q, gr_ptr R, gr_srcptr A, slong lenA, gr_srcptr B, slong lenB, gr_ctx_t ctx);
WARN_UNUSED_RESULT int _gr_poly_divrem_basecase(gr_ptr Q, gr_ptr R, gr_srcptr A, slong lenA, gr_srcptr B, slong lenB, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_divrem_basecase(gr_poly_t Q, gr_poly_t R, const gr_poly_t A, const gr_poly_t B, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_divrem(gr_ptr Q, gr_ptr R, gr_srcptr A, slong lenA, gr_srcptr B, slong lenB, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_divrem(gr_poly_t Q, gr_poly_t R, const gr_poly_t A, const gr_poly_t B, gr_ctx_t ctx);

/* todo: div with fast divisibility checking; rem; divexact */

WARN_UNUSED_RESULT int _gr_poly_inv_series(gr_ptr Qinv, gr_srcptr Q, slong Qlen, slong len, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_inv_series(gr_poly_t Qinv, const gr_poly_t Q, slong len, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_evaluate_rectangular(gr_ptr res, gr_srcptr poly, slong len, gr_srcptr x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_evaluate_rectangular(gr_ptr res, const gr_poly_t poly, gr_srcptr x, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_evaluate_horner(gr_ptr res, gr_srcptr poly, slong len, gr_srcptr x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_evaluate_horner(gr_ptr res, const gr_poly_t poly, gr_srcptr x, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_evaluate(gr_ptr res, gr_srcptr poly, slong len, gr_srcptr x, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_evaluate(gr_ptr res, const gr_poly_t poly, gr_srcptr x, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_evaluate_other_horner(gr_ptr res, gr_srcptr f, slong len, const gr_srcptr x, gr_ctx_t x_ctx, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_evaluate_other_horner(gr_ptr res, const gr_poly_t f, gr_srcptr a, gr_ctx_t a_ctx, gr_ctx_t ctx);
WARN_UNUSED_RESULT int _gr_poly_evaluate_other_rectangular(gr_ptr res, gr_srcptr f, slong len, const gr_srcptr x, gr_ctx_t x_ctx, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_evaluate_other_rectangular(gr_ptr res, const gr_poly_t f, gr_srcptr a, gr_ctx_t a_ctx, gr_ctx_t ctx);
WARN_UNUSED_RESULT int _gr_poly_evaluate_other(gr_ptr res, gr_srcptr f, slong len, const gr_srcptr x, gr_ctx_t x_ctx, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_evaluate_other(gr_ptr res, const gr_poly_t f, gr_srcptr a, gr_ctx_t a_ctx, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_taylor_shift_horner(gr_ptr res, gr_srcptr poly, slong len, gr_srcptr c, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_taylor_shift_horner(gr_poly_t res, const gr_poly_t f, gr_srcptr c, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_taylor_shift_divconquer(gr_ptr res, gr_srcptr poly, slong len, gr_srcptr c, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_taylor_shift_divconquer(gr_poly_t res, const gr_poly_t f, gr_srcptr c, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_taylor_shift(gr_ptr res, gr_srcptr poly, slong len, gr_srcptr c, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_taylor_shift(gr_poly_t res, const gr_poly_t f, gr_srcptr c, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_compose_horner(gr_ptr res, gr_srcptr poly1, slong len1, gr_srcptr poly2, slong len2, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_compose_horner(gr_poly_t res, const gr_poly_t poly1, const gr_poly_t poly2, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_compose_divconquer(gr_ptr res, gr_srcptr poly1, slong len1, gr_srcptr poly2, slong len2, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_compose_divconquer(gr_poly_t res, const gr_poly_t poly1, const gr_poly_t poly2, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_compose(gr_ptr res, gr_srcptr poly1, slong len1, gr_srcptr poly2, slong len2, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_compose(gr_poly_t res, const gr_poly_t poly1, const gr_poly_t poly2, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_derivative(gr_ptr res, gr_srcptr poly, slong len, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_derivative(gr_poly_t res, const gr_poly_t poly, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_integral(gr_ptr res, gr_srcptr poly, slong len, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_integral(gr_poly_t res, const gr_poly_t poly, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_make_monic(gr_ptr res, gr_srcptr poly, slong len, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_make_monic(gr_poly_t res, const gr_poly_t src, gr_ctx_t ctx);

WARN_UNUSED_RESULT truth_t _gr_poly_is_monic(gr_srcptr poly, slong len, gr_ctx_t ctx);
WARN_UNUSED_RESULT truth_t gr_poly_is_monic(const gr_poly_t res, gr_ctx_t ctx);

WARN_UNUSED_RESULT int _gr_poly_gcd_euclidean(gr_ptr G, slong * lenG, gr_srcptr A, slong lenA, gr_srcptr B, slong lenB, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_gcd_euclidean(gr_poly_t G, const gr_poly_t A, const gr_poly_t B, gr_ctx_t ctx);
WARN_UNUSED_RESULT int _gr_poly_gcd(gr_ptr G, slong * lenG, gr_srcptr A, slong lenA, gr_srcptr B, slong lenB, gr_ctx_t ctx);
WARN_UNUSED_RESULT int gr_poly_gcd(gr_poly_t G, const gr_poly_t A, const gr_poly_t B, gr_ctx_t ctx);

/* Roots */

typedef int ((*gr_poly_roots_op)(gr_vec_t, gr_vec_t, const gr_poly_t, int, gr_ctx_ptr));
#define GR_POLY_ROOTS_OP(ctx, NAME) (((gr_poly_roots_op *) ctx->methods)[GR_METHOD_ ## NAME])
GR_POLY_INLINE WARN_UNUSED_RESULT int gr_poly_roots(gr_vec_t roots, gr_vec_t mult, const gr_poly_t poly, int flags, gr_ctx_t ctx) { return GR_POLY_ROOTS_OP(ctx, POLY_ROOTS)(roots, mult, poly, flags, ctx); }

typedef int ((*gr_poly_roots_op_other)(gr_vec_t, gr_vec_t, const gr_poly_t, gr_ctx_ptr, int, gr_ctx_ptr));
#define GR_POLY_ROOTS_OP_OTHER(ctx, NAME) (((gr_poly_roots_op_other *) ctx->methods)[GR_METHOD_ ## NAME])
GR_POLY_INLINE WARN_UNUSED_RESULT int gr_poly_roots_other(gr_vec_t roots, gr_vec_t mult, const gr_poly_t poly, gr_ctx_t poly_ctx, int flags, gr_ctx_t ctx) { return GR_POLY_ROOTS_OP_OTHER(ctx, POLY_ROOTS_OTHER)(roots, mult, poly, poly_ctx, flags, ctx); }


#ifdef __cplusplus
}
#endif

#endif
