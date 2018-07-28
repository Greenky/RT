# define SCR_SIZE 800
# define FALSE 0
# define TRUE 1
# define DISTANCE 1

# define STEP (1.0 / SCR_SIZE)

# define LEFT_BOUND (-(SCR_SIZE / 2))
# define TOP_BOUND (-(SCR_SIZE / 2))

# define A 0
# define B 1
# define C 2

# define DIVISION 0
# define MULTIPLICATION 1

# define INF 999999

# define VEC(a1, a2, a3) (float3){a1, a2, a3}

enum	e_error {NUM_OF_ARG, ERROR, CAM_ERROR};
enum	e_figures {SPHERE, CYLINDER, CONE, PLANE, ELLIPSOID};
enum	e_lights {AMBIENT, POINT, DIRECT};

typedef struct		s_channel
{
	float			red;
	float			green;
	float			blue;
}					t_channel;

typedef struct	s_ray
{
	float3	origin;
	float3	direction;
}				t_ray;

typedef struct		s_coord_sys
{
	float3		b_x;
	float3		b_y;
	float3		b_z;
}					t_coord_sys;

typedef struct	s_camera
{
	float3		origin;
	t_coord_sys		initial_basis;
	t_coord_sys		basis;
	float3		angle_rot;
	int				is_set;

	double			dest;//TODO delete if unnecessary

}				t_camera;

typedef struct		s_light // ADDED TYPE, fix
{
	int				type;
	float			intensity;
	float3			origin;
	t_channel		color;
	float3			direct;
}					t_light;

struct s_intersect;
typedef struct		s_objects
{
	int					type;
	t_channel			color;
	float				radius;
	float				angle_coef;
	float				mirror_coef;
	float				transperent_coef;
	float3				origin;
	float3				normal;
	float3				axis_dimensions;//размеры осей x y z для эллипсоида
	t_coord_sys			basis;
	int					bling_phong;
}					t_objects;

typedef struct		s_intersect
{
	float						distance;
	float3						point;//точка пересечения фигуры и луча
	float3						normal;
	__constant t_objects		*fig;
}					t_intersect;

typedef struct	s_cl_data
{
	int			num_of_objects;
	int			num_of_lights;
	int			reflect_rate;
	int			max_reflections;
	t_camera	camera;
}				t_cl_data;

// =====================================================================================================================
// FUNCTIONS PROTOTYPES START
// =====================================================================================================================

void	ft_bzero(void *s, size_t n);

float	find_square(float a);
float	vec_distance(float3 v1, float3 v2);
float	vec_length(float3 v);

float3	vect_diff(float3 v1, float3 v2);
float3	vect_sum(float3 v1, float3 v2);
float3	vect_mult_scalar(float3 v1, float multiplier);
float	vect_scalar_mult(float3 v1, float3 v2);
float3	vect_cross_product(float3 a, float3 b);
float3	normalize_vector(float3 a);
float3	change_vector(float3 v,  int flag, float3 mult_coef);

float3			matrix_mult_vect(t_coord_sys a, float3 v);
t_coord_sys		matrix_mult_matrix(t_coord_sys a, t_coord_sys b);
t_coord_sys		count_inverse_matrix(t_coord_sys a);
void			normalize_basis(t_coord_sys *a);

t_ray		compute_ray(t_camera *camera, float2 pixel, int aliasing);
int			find_the_root(float coefficient[3], float discriminant, float t[2]);
float		find_sphere_discriminant(t_ray r,__constant t_objects *fig, float coefficient[3]);
void		sphere_find_closest_intersect(t_ray r, t_intersect *inter);
float		find_cyl_discriminant(t_ray r, float radius, float *coefficient);
void		cyl_find_closest_intersect(t_ray r, t_intersect *inter);

float		find_cone_discriminant(t_ray r, float *coefficient, float coef);
void		cone_find_closest_intersect(t_ray r, t_intersect *inter);
void		plane_find_closest_intersect(t_ray r, t_intersect *inter);

t_ray		find_ray_for_imaginary_sphere(t_ray ray, t_objects *ellipsoid);
void		ellipsoid_find_closest_intersect(t_ray ray, t_intersect *inter);

void		choose_intersection(t_ray primary_ray, t_intersect *tmp_inter);
t_intersect	find_closest_inter(t_cl_data cl_data, __constant t_objects *objects, t_ray primary_ray);

float3		find_normal_to_sphere(__constant t_objects *sphere, float3 inter);
float3		find_normal_to_cylinder(__constant t_objects *cyl, float3 inter);
float3		find_normal_to_cone(__constant t_objects *cone, float3 inter);
float3		find_normal_to_plane(__constant t_objects *plane, float3 inter);
float3		choose_normal(__constant t_objects *figure, float3 inter);

int			is_shadows_here(t_ray light_ray, float3 normal, t_ray r);
void		add_coef(t_channel *coef1, t_channel coef2, float coef);
t_ray		find_light_ray(float3 origin, float3 end);
int			is_figure_first_inter_by_light(t_cl_data cl_data,__constant  t_objects *objects, t_ray light_ray,
											  t_intersect closest_inter);
float		*find_cos_angle(t_ray light_ray, t_intersect closest_inter,
							 float3 normal, t_ray r);
t_channel	find_lamp_coef(t_cl_data cl_data, __constant t_objects *objects, __constant t_light *current_lamp, t_intersect closest_inter, t_ray r);

unsigned int	find_color_channel(float fig_color_channel, float light_color_channel, int step);

unsigned int	find_color_hex(t_channel light_coef, t_intersect closest_inter);

unsigned int	find_color(t_cl_data cl_data, __constant t_objects *objects, __constant t_light *lights, t_intersect closest_inter, t_ray r);

t_intersect		find_closest_reflected_inter(t_cl_data cl_data, __constant t_objects *objects, t_ray ray, __constant t_objects *this);
t_channel		int_to_channels(int col);
// =====================================================================================================================
// FUNCTIONS PROTOTYPES END
// =====================================================================================================================


void	ft_bzero(void *s, size_t n)
{
	unsigned long		idx;
	unsigned char		*a;

	idx = 0;
	a = (unsigned char*)s;
	while (idx < n)
	{
		a[idx] = '\0';
		idx++;
	}
}

// =====================================================================================================================
// MATH FUNCTIONS START
// =====================================================================================================================
// =====================================================================================================================
// ALGEBRAIC FUNCTIONS START
// =====================================================================================================================

float	find_square(float a)
{
	return (a * a);
}

float	vec_distance(float3 v1, float3 v2)
{
	float	div_x;
	float	div_y;
	float	div_z;

	div_x = v2.x - v1.x;
	div_y = v2.y - v1.y;
	div_z = v2.z - v1.z;
	return (sqrt(div_x * div_x + div_y * div_y + div_z * div_z));
}

float	vec_length(float3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

// =====================================================================================================================
// ALGEBRAIC FUNCTIONS END
// =====================================================================================================================

// =====================================================================================================================
// VECTOR FUNCTIONS START
// =====================================================================================================================

float3	vect_diff(float3 v1, float3 v2)
{
	float3	result_vector;

	result_vector.x = v1.x - v2.x;
	result_vector.y = v1.y - v2.y;
	result_vector.z = v1.z - v2.z;
	return (result_vector);
}

float3	vect_sum(float3 v1, float3 v2)
{
	float3	result_vector;

	result_vector.x = v1.x + v2.x;
	result_vector.y = v1.y + v2.y;
	result_vector.z = v1.z + v2.z;
	return (result_vector);
}

float3	vect_mult_scalar(float3 v1, float multiplier)
{
	float3	result_vector;

	result_vector.x = v1.x * multiplier;
	result_vector.y = v1.y * multiplier;
	result_vector.z = v1.z * multiplier;
	return (result_vector);
}

float		vect_scalar_mult(float3 v1, float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float3	vect_cross_product(float3 a, float3 b)
{
	float3 c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

float3	normalize_vector(float3 a)
{
	float		coef;
	float3	normal;
	float		len;

	len = vec_length(a);
	if (len == 0)
		return VEC(0, 0, 0);
	coef = 1.0f / len;
	normal.x = a.x * coef;
	normal.y = a.y * coef;
	normal.z = a.z * coef;
	return (normal);
}

float3	change_vector(float3 v,  int flag, float3 mult_coef)
{
	if (flag == DIVISION)
	{
		v.x /= mult_coef.x;
		v.y /= mult_coef.y;
		v.z /= mult_coef.z;
	}
	else if (flag == MULTIPLICATION)
	{
		v.x *= mult_coef.x;
		v.y *= mult_coef.y;
		v.z *= mult_coef.z;
	}
	return (v);
}


// =====================================================================================================================
// VECTOR FUNCTIONS END
// =====================================================================================================================

// =====================================================================================================================
// MATRIX FUNCTIONS START
// =====================================================================================================================

float3		matrix_mult_vect(t_coord_sys a, float3 v)
{
	float3		new_v;

	new_v.x = a.b_x.x * v.x + a.b_y.x * v.y + a.b_z.x * v.z;
	new_v.y = a.b_x.y * v.x + a.b_y.y * v.y + a.b_z.y * v.z;
	new_v.z = a.b_x.z * v.x + a.b_y.z * v.y + a.b_z.z * v.z;
	return (new_v);
}

t_coord_sys		matrix_mult_matrix(t_coord_sys a, t_coord_sys b)
{
	t_coord_sys		new;

	new.b_x.x = a.b_x.x * b.b_x.x + a.b_y.x * b.b_x.y + a.b_z.x * b.b_x.z;
	new.b_x.y = a.b_x.y * b.b_x.x + a.b_y.y * b.b_x.y + a.b_z.y * b.b_x.z;
	new.b_x.z = a.b_x.z * b.b_x.x + a.b_y.z * b.b_x.y + a.b_z.z * b.b_x.z;

	new.b_y.x = a.b_x.x * b.b_y.x + a.b_y.x * b.b_y.y + a.b_z.x * b.b_y.z;
	new.b_y.y = a.b_x.y * b.b_y.x + a.b_y.y * b.b_y.y + a.b_z.y * b.b_y.z;
	new.b_y.z = a.b_x.z * b.b_y.x + a.b_y.z * b.b_y.y + a.b_z.z * b.b_y.z;

	new.b_z.x = a.b_x.x * b.b_z.x + a.b_y.x * b.b_z.y + a.b_z.x * b.b_z.z;
	new.b_z.y = a.b_x.y * b.b_z.x + a.b_y.y * b.b_z.y + a.b_z.y * b.b_z.z;
	new.b_z.z = a.b_x.z * b.b_z.x + a.b_y.z * b.b_z.y + a.b_z.z * b.b_z.z;

	return (new);
}

t_coord_sys		count_inverse_matrix(t_coord_sys a)
{
	float		determinant;
	t_coord_sys	m;

	determinant = a.b_x.x * (a.b_y.y * a.b_z.z - a.b_z.y * a.b_y.z) -
				  a.b_y.x * (a.b_x.y * a.b_z.z - a.b_z.y * a.b_x.z) +
				  a.b_z.x * (a.b_x.y * a.b_y.z - a.b_y.y * a.b_x.z);
	determinant = 1 / determinant;
	m.b_x.x = (a.b_y.y * a.b_z.z - a.b_z.y * a.b_y.z) * determinant;
	m.b_x.y = (a.b_z.y * a.b_x.z - a.b_x.y * a.b_z.z) * determinant;
	m.b_x.z = (a.b_x.y * a.b_y.z - a.b_y.y * a.b_x.z) * determinant;
	m.b_y.x = (a.b_z.x * a.b_y.z - a.b_y.x * a.b_z.z) * determinant;
	m.b_y.y = (a.b_x.x * a.b_z.z - a.b_z.x * a.b_x.z) * determinant;
	m.b_y.z = (a.b_y.x * a.b_x.z - a.b_x.x * a.b_y.z) * determinant;
	m.b_z.x = (a.b_y.x * a.b_z.y - a.b_z.x * a.b_y.y) * determinant;
	m.b_z.y = (a.b_z.x * a.b_x.y - a.b_x.x * a.b_z.y) * determinant;
	m.b_z.z = (a.b_x.x * a.b_y.y - a.b_y.x * a.b_x.y) * determinant;
	return (m);
}

void			normalize_basis(t_coord_sys *a)
{
	a->b_x = normalize_vector(a->b_x);
	a->b_y = normalize_vector(a->b_y);
	a->b_z = normalize_vector(a->b_z);
}

// =====================================================================================================================
// MATRIX FUNCTIONS END
// =====================================================================================================================
// =====================================================================================================================
// MATH FUNCTIONS END
// =====================================================================================================================

t_ray		compute_ray(t_camera *camera, float2 pixel, int aliasing)
{
	t_ray	r;
	float	vertical;
	float	horizontal;

	r.origin = camera->origin;
	vertical = (float)((TOP_BOUND + pixel.y) * STEP);
	horizontal = (float)((LEFT_BOUND + pixel.x) * STEP);
	r.direction = normalize(matrix_mult_vect(camera->basis,
													VEC(horizontal, -vertical, -DISTANCE)));
	return (r);
}
// =====================================================================================================================
// OBJECTS INTERSECTIONS START
// =====================================================================================================================
// =====================================================================================================================
// SPHERE INTERSECTION START
// =====================================================================================================================
int		find_the_root(float coefficient[3], float discriminant, float t[2])
{
	float	square_d;

	if (discriminant < 0)
		return (FALSE);
	else if (discriminant == 0)
	{
		t[0] = -coefficient[B] / coefficient[A];
		t[1] = -1;
	}
	else
	{
		square_d = sqrtf(discriminant);
		t[0] = (-coefficient[B] + square_d) / coefficient[A];
		t[1] = (-coefficient[B] - square_d) / coefficient[A];
	}
	if (t[0] < 0 && t[1] < 0)
		return (FALSE);
	if ((t[1] < t[0] && t[1] >= 0) || t[0] < 0)
		t[0] = t[1];
	return (TRUE);
}

float	find_sphere_discriminant(t_ray r,__constant  t_objects *fig, float coefficient[3])
{
	float		discriminant;
	float3	cam_origin;

	cam_origin = vect_diff(r.origin, fig->origin);
	coefficient[A] = vect_scalar_mult(r.direction, r.direction);
	coefficient[B] = vect_scalar_mult(r.direction, cam_origin);
	coefficient[C] = vect_scalar_mult(cam_origin, cam_origin)
					 - find_square(fig->radius);
	discriminant = find_square(coefficient[B]) -
				   coefficient[A] * coefficient[C];
	return (discriminant);
}

void	sphere_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float	discriminant;
	float	t[2];
	float	coefficient[3];

	discriminant = find_sphere_discriminant(r, inter->fig, coefficient);
	if (!find_the_root(coefficient, discriminant, t))
		inter->distance = INF;
	else
	{
		inter->point = vect_sum(r.origin, vect_mult_scalar(r.direction, t[0]));
		inter->distance = t[0];
	}
}
// =====================================================================================================================
// SPHERE INTERSECTION END
// =====================================================================================================================

// =====================================================================================================================
// CYLINDER INTERSECTION START
// =====================================================================================================================
float	find_cyl_discriminant(t_ray r, float radius, float *coefficient)
{
	float	discriminant;

	coefficient[A] = find_square(r.direction.x) + find_square(r.direction.y);
	coefficient[B] = r.origin.x * r.direction.x + r.origin.y * r.direction.y;
	coefficient[C] = find_square(r.origin.x) + find_square(r.origin.y) -
					 find_square(radius);
	discriminant = find_square(coefficient[B]) -
				   coefficient[A] * coefficient[C];
	return (discriminant);
}

void	cyl_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float	discriminant;
	float	t[2];
	float	coefficient[3];
	t_ray	r_cyl_sys;

	r_cyl_sys.origin = vect_diff(r.origin, inter->fig->origin);
	r_cyl_sys.origin =
			matrix_mult_vect(count_inverse_matrix(inter->fig->basis),
							 r_cyl_sys.origin);
	r_cyl_sys.direction =
			matrix_mult_vect(count_inverse_matrix(inter->fig->basis), r.direction);
	discriminant = find_cyl_discriminant(r_cyl_sys,
										 inter->fig->radius, coefficient);
	if (!find_the_root(coefficient, discriminant, t))
		inter->distance = INF;
	else
	{
		inter->point = vect_sum(r.origin, vect_mult_scalar(r.direction, t[0]));
		inter->distance = t[0];
	}
}
// =====================================================================================================================
// CYLINDER INTERSECTION END
// =====================================================================================================================

// =====================================================================================================================
// CONE INTERSECTION START
// =====================================================================================================================
float	find_cone_discriminant(t_ray r, float *coefficient, float coef)
{
	float	discriminant;

	coef = find_square(coef);
	coefficient[A] = find_square(r.direction.x) + find_square(r.direction.y) -
					 find_square(r.direction.z) * coef;
	coefficient[B] = r.origin.x * r.direction.x + r.origin.y * r.direction.y -
					 r.origin.z * r.direction.z * coef;
	coefficient[C] = find_square(r.origin.x) + find_square(r.origin.y) -
					 find_square(r.origin.z) * coef;
	discriminant = find_square(coefficient[B]) -
				   coefficient[A] * coefficient[C];
	return (discriminant);
}

void	cone_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float	discriminant;
	float	t[2];
	float	coefficient[3];
	t_ray	r_cone_sys;

	r_cone_sys.origin = vect_diff(r.origin, inter->fig->origin);
	r_cone_sys.origin =
			matrix_mult_vect(count_inverse_matrix(inter->fig->basis),
							 r_cone_sys.origin);
	r_cone_sys.direction =
			matrix_mult_vect(count_inverse_matrix(inter->fig->basis), r.direction);
	discriminant = find_cone_discriminant(r_cone_sys, coefficient,
										  inter->fig->angle_coef);
	if (!find_the_root(coefficient, discriminant, t))
		inter->distance = INF;
	else
	{
		inter->point = vect_sum(r.origin, vect_mult_scalar(r.direction, t[0]));
		inter->distance = t[0];
	}
}
// =====================================================================================================================
// CONE INTERSECTION END
// =====================================================================================================================

// =====================================================================================================================
// PLANE INTERSECTION START
// =====================================================================================================================
void	plane_find_closest_intersect(t_ray r, t_intersect *inter)
{
	float3		origin_diff;
	float		n_mult_dir;

	n_mult_dir = vect_scalar_mult(inter->fig->basis.b_z, r.direction);
	if (n_mult_dir == 0)
		inter->distance = INF;
	else
	{
		origin_diff = vect_diff(inter->fig->origin, r.origin);
		inter->distance =
				(vect_scalar_mult(inter->fig->basis.b_z, origin_diff)) /
				n_mult_dir;
		if (inter->distance < 0)
			inter->distance = INF;
		if (inter->distance != INF)
		{
			inter->point = vect_sum(r.origin,
									vect_mult_scalar(r.direction, inter->distance));
		}
	}
}
// =====================================================================================================================
// PLANE INTERSECTION END
// =====================================================================================================================

// =====================================================================================================================
// ELLIPSOID INTERSECTION START
// =====================================================================================================================

void	ellipsoid_find_closest_intersect(t_ray ray, t_intersect *inter)
{
	t_ray		imaginary_sphere_ray;

	imaginary_sphere_ray = find_ray_for_imaginary_sphere(ray, inter->fig);
	sphere_find_closest_intersect(imaginary_sphere_ray, inter);
	if (inter->distance == INFINITY)
		return ;
	else
	{
		inter->point = vect_diff(inter->point, inter->fig->origin);
		inter->point = matrix_mult_vect(count_inverse_matrix(inter->fig->basis), inter->point);
		inter->point = scale_vector(inter->point, MULTIPLICATION, inter->fig->axis_dimensions);
		inter->point = vect_sum(inter->point, inter->fig->origin);
		inter->point = matrix_mult_vect(inter->fig->basis, inter->point);
		inter->distance = distance(inter->point, ray.origin);
	}
}

t_ray	find_ray_for_imaginary_sphere(t_ray ray, t_objects *ellipsoid)
{
	t_ray		new_ray;

	new_ray.origin = vect_diff(ray.origin, ellipsoid->origin);
	new_ray.origin = matrix_mult_vect(count_inverse_matrix(ellipsoid->basis), new_ray.origin);
	new_ray.origin = scale_vector(new_ray.origin, DIVISION, ellipsoid->axis_dimensions);
	new_ray.origin = vect_sum(new_ray.origin, ellipsoid->origin);
	new_ray.origin = matrix_mult_vect(ellipsoid->basis, new_ray.origin);
	new_ray.direction = matrix_mult_vect(count_inverse_matrix(ellipsoid->basis), ray.direction);
	new_ray.direction = scale_vector(new_ray.direction, DIVISION, ellipsoid->axis_dimensions);
	new_ray.direction = matrix_mult_vect(ellipsoid->basis, new_ray.direction);
	return (new_ray);
}

// =====================================================================================================================
// ELLIPSOID INTERSECTION END
// =====================================================================================================================

// =====================================================================================================================
// FINDING INTERSECTION START
// =====================================================================================================================
void		choose_intersection(t_ray primary_ray, t_intersect *tmp_inter)
{
	if (tmp_inter->fig->type == SPHERE)
		sphere_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == CYLINDER)
		cyl_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == CONE)
		cone_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == PLANE)
		plane_find_closest_intersect(primary_ray, tmp_inter);
	else if (tmp_inter->fig->type == ELLIPSOID)
		ellipsoid_find_closest_intersect(primary_ray, tmp_inter);
}

t_intersect	find_closest_inter(t_cl_data cl_data, __constant t_objects *objects, t_ray primary_ray)
{
	t_intersect	tmp_inter;
	t_intersect	closest_inter;
	int			current;

	closest_inter.distance = INF;
	current = 0;
	while (current < cl_data.num_of_objects)
	{
		tmp_inter.fig = &objects[current];
		choose_intersection(primary_ray, &tmp_inter);
		if (tmp_inter.distance < closest_inter.distance)
			closest_inter = tmp_inter;
		current++;
	}
	return (closest_inter);
}
// =====================================================================================================================
// FINDING INTERSECTION END
// =====================================================================================================================
// =====================================================================================================================
// OBJECTS INTERSECTIONS END
// =====================================================================================================================

// =====================================================================================================================
// FINDING COLOR START
// =====================================================================================================================
// =====================================================================================================================
// NORMAL FUNCTIONS START
// =====================================================================================================================

float3	find_normal_to_sphere(__constant t_objects *sphere, float3 inter)
{
	float3		normal_to_sphere;
	float3		normal_to_sphere_unit;

	normal_to_sphere = vect_diff(inter, sphere->origin);
	normal_to_sphere_unit = vect_mult_scalar(normalize_vector(normal_to_sphere), -1);
	return (normal_to_sphere_unit);
}

float3	find_normal_to_cylinder(__constant t_objects *cyl, float3 inter)
{
	float3		normal;
	float3		normal_unit;
	float			t;
	float3		orig_inter;

	orig_inter = vect_diff(inter, cyl->origin);
	t = vect_scalar_mult(orig_inter, cyl->basis.b_z) /
		vect_scalar_mult(cyl->basis.b_z, cyl->basis.b_z);
	normal = vect_diff(vect_sum(cyl->origin,
								vect_mult_scalar(cyl->basis.b_z, t)), inter);
	normal_unit = normalize_vector(normal);
	return (normal_unit);
}

float3	find_normal_to_cone(__constant t_objects *cone, float3 inter)
{
	float3		normal;
	float3		normal_unit;
	float			height;
	float3		inter_orig;

	inter_orig = vect_diff(cone->origin, inter);
	height = -vect_scalar_mult(inter_orig, inter_orig) /
			 vect_scalar_mult(cone->basis.b_z, inter_orig);
	normal = vect_diff(vect_sum(cone->origin, vect_mult_scalar(cone->basis.b_z,
															   height)), inter);
	normal_unit = normalize_vector(normal);
	return (normal_unit);
}

float3	find_normal_to_plane(__constant t_objects *plane, float3 inter)
{
	(void)inter;
	return (vect_mult_scalar(plane->basis.b_z, -1));
}

float3	choose_normal(__constant t_objects *figure, float3 inter)
{
	if (figure->type == SPHERE)
		return (find_normal_to_sphere(figure, inter));
	else if (figure->type == CYLINDER)
		return (find_normal_to_cylinder(figure, inter));
	else if (figure->type == CONE)
		return (find_normal_to_cone(figure, inter));
	else if (figure->type == PLANE)
		return (find_normal_to_plane(figure, inter));
	else
		return VEC(1, 1, 1);
}
// =====================================================================================================================
// NORMAL FUNCTIONS END
// =====================================================================================================================

int			is_shadows_here(t_ray light_ray, float3 normal, t_ray r)
{
	float	is_light_with_cam;

	is_light_with_cam = vect_scalar_mult(r.direction, normal) *
						vect_scalar_mult(light_ray.direction, normal);
	if (is_light_with_cam >= 0)
		return (TRUE);
	else
		return (FALSE);
}

void		add_coef(t_channel *coef1, t_channel coef2, float coef)
{
	coef1->blue += coef2.blue * coef;
	coef1->green += coef2.green * coef;
	coef1->red += coef2.red * coef;
}

t_ray		find_light_ray(float3 origin, float3 end)
{
	t_ray		light_ray;

	light_ray.origin = origin;
	light_ray.direction = vect_diff(end, origin);
	return (light_ray);
}

int			is_figure_first_inter_by_light(t_cl_data cl_data,__constant t_objects *objects, t_ray light_ray,
											  t_intersect closest_inter)
{
	t_intersect		clost_to_light;
	float			distance_to_light;
	int 			current;

	current = 0;
	distance_to_light = vec_distance(light_ray.origin, closest_inter.point);
	while (current < cl_data.num_of_objects)
	{
		clost_to_light.fig = &objects[current];
		if (clost_to_light.fig->type != closest_inter.fig->type)
		{
			choose_intersection(light_ray, &clost_to_light);
			if (clost_to_light.distance != INF)
				clost_to_light.distance =
						distance(light_ray.origin, clost_to_light.point);
			if (clost_to_light.distance < distance_to_light)
				return (FALSE);
		}
		current++;
	}
	return (TRUE);
}

float		*find_cos_angle(t_ray light_ray, t_intersect closest_inter,
							 float3 normal, t_ray r)
{
	float3	light_ray_unit;
	float	*cos_angle;
	float3	bisector;

	cos_angle = malloc(sizeof(float) * 2);
	light_ray_unit = normalize(light_ray.direction);
	cos_angle[0] = vect_scalar_mult(light_ray_unit, normal);
	if (cos_angle[0] < 0)
		cos_angle[0] = 0;
	bisector = normalize_vector(vect_sum(r.direction, light_ray_unit));
	cos_angle[1] = (float)(pow(vect_scalar_mult(bisector, normal),
							   closest_inter.fig->bling_phong) *
						   pow(closest_inter.fig->bling_phong, 0.75) * 2);
	if (cos_angle[1] < 0)
		cos_angle[1] = 0;
	return (cos_angle);
}

t_channel				int_to_channels(int col)
{
	t_channel channels;

	channels.blue = col & 255;
	channels.green = col >> 8 & 255;
	channels.red = col >> 16 & 255;
	return (channels);
}

t_intersect	find_closest_reflected_inter(t_cl_data cl_data, __constant t_objects *objects, t_ray ray, __constant t_objects *this)
{
	t_intersect	tmp_inter;
	t_intersect	closest_inter;
	int current;

	closest_inter.distance = INFINITY;
	current = 0;
	while (current < cl_data.num_of_objects)
	{
		tmp_inter.fig = &objects[current];
		choose_intersection(ray, &tmp_inter);
		if (tmp_inter.distance < closest_inter.distance && tmp_inter.fig != this)
			closest_inter = tmp_inter;
		current++;
	}
	return (closest_inter);
}
t_channel	find_lamp_coef(t_cl_data cl_data, __constant t_objects *objects, __constant t_light *current_lamp,
							t_intersect closest_inter, t_ray r, __constant t_light *lights)
{
	float3			bisector;
	float3			light_ray_unit;
	t_ray			light_ray;
	t_channel		lamp_coef;
	float3			normal;
	float			cos_angle[2];
	t_ray			reflected_ray;
	t_intersect		reflected_inter;
	float 			a;

	ft_bzero(&lamp_coef, sizeof(t_channel));
	if (current_lamp->type == AMBIENT)
		add_coef(&lamp_coef, current_lamp->color, current_lamp->intensity);
	else
	{
		light_ray = find_light_ray(current_lamp->origin, closest_inter.point);
		normal = choose_normal(closest_inter.fig, closest_inter.point);
		if (closest_inter.fig->mirror_coef > 0 && cl_data.reflect_rate < cl_data.max_reflections)
		{
			cl_data.reflect_rate++;
			reflected_ray.origin = closest_inter.point;
			a = 2 * dot(r.direction, closest_inter.normal);
			reflected_ray.direction = r.direction - (closest_inter.normal * a);
			reflected_inter = find_closest_reflected_inter(cl_data, objects, reflected_ray, closest_inter.fig);
			if (reflected_inter.distance != INFINITY)
				add_coef(&lamp_coef, int_to_channels(find_color(cl_data, lights, objects, reflected_inter, reflected_ray)),
					closest_inter.fig->mirror_coef);
		}
		if (!is_shadows_here(light_ray, normal, r) ||
			!is_figure_first_inter_by_light(cl_data, objects, light_ray, closest_inter))
			return (lamp_coef);

		light_ray_unit = normalize(light_ray.direction);
		cos_angle[0] = vect_scalar_mult(light_ray_unit, normal);
		if (cos_angle[0] < 0)
			cos_angle[0] = 0;
		bisector = normalize_vector(vect_sum(r.direction, light_ray_unit));
		cos_angle[1] = (float)(pow(vect_scalar_mult(bisector, normal),
				closest_inter.fig->bling_phong) *
		pow(closest_inter.fig->bling_phong, 0.75) * 2);
		if (cos_angle[1] < 0)
			cos_angle[1] = 0;

		add_coef(&lamp_coef, current_lamp->color, cos_angle[0] *
												  current_lamp->intensity);
		add_coef(&lamp_coef, (t_channel){1, 1, 1}, cos_angle[1] *
												   current_lamp->intensity);
	}
	return (lamp_coef);
}

unsigned int	find_color_channel(float fig_color_channel,
							   float light_color_channel, int step)
{
	unsigned int	mult;

	if (fig_color_channel < 0 || light_color_channel < 0)
		return (0);
	mult = (unsigned int)(fig_color_channel * light_color_channel) >> 8;
	if (mult > 0xFF)
		mult = 0xFF;
	return (mult << step);
}

unsigned int	find_color_hex(t_channel light_coef, t_intersect closest_inter)
{
	unsigned int	color_hex;

	color_hex = 0;
	color_hex += find_color_channel(closest_inter.fig->color.red,
									light_coef.red, 16);
	color_hex += find_color_channel(closest_inter.fig->color.green,
									light_coef.green, 8);
	color_hex += find_color_channel(closest_inter.fig->color.blue,
									light_coef.blue, 0);
	return (color_hex);
}

t_channel				int_to_channels(int col)
{
	t_channel channels;

	channels.blue = col & 255;
	channels.green = col >> 8 & 255;
	channels.red = col >> 16 & 255;
	return (channels);
}

unsigned int	find_color(t_cl_data cl_data, __constant t_objects *objects, __constant t_light *lights, t_intersect closest_inter, t_ray r)
{
	__constant t_light		*current_lamp;
	t_channel	light_coef;
	int			current;

	ft_bzero(&light_coef, sizeof(t_channel));
	current = 0;
	while (current < cl_data.num_of_lights)
	{
		current_lamp = lights + current;
		add_coef(&light_coef, find_lamp_coef(cl_data, objects, current_lamp,
											 closest_inter, r, lights), 1);
		current++;
	}
	return (find_color_hex(light_coef, closest_inter));
}
// =====================================================================================================================
// FINDING COLOR END
// =====================================================================================================================


// =====================================================================================================================
//
// =====================================================================================================================

__kernel void	renderer(t_cl_data cl_data,
						  __global unsigned int *image,
						  __constant t_objects *objects,
						  __constant t_light *lights)
{
	t_ray		primary_ray;
	unsigned int	color;
	t_intersect	closest_inter;
//	int id = get_global_id(0);
	int	j = get_global_id(0);
	int	i = get_global_id(1);
	float2	pixel;

	pixel.x = j;
	pixel.y = i;
	primary_ray = compute_ray(&cl_data.camera, pixel, antialias);//
	closest_inter = find_closest_inter(cl_data, objects, primary_ray);
	cl_data.reflect_rate = 0;
	if (closest_inter.distance == INF)
		color = 0;
	else
		color = find_color(cl_data, objects,lights, closest_inter, primary_ray);
	*(image + j + i * SCR_SIZE) = color;
}
