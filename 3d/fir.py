import add
import math


#points
start_point = [1, 1, 1]
end_point = [1, 2, 1]

#colors
brown = [150, 75, 0]
red = [255, 0, 0]
green = [0, 150, 0]
dark_green = [0, 125, 0]
#shapes

#TODO
def branch(branch_start, branch_end):
    add.cylinder(branch_start, branch_end, 0.1, 4, dark_green)
    #pitagoro teorema gaut ilgi su x ir z coord
    branch_length = math.sqrt(pow(branch_end[0] - branch_start[0], 2) + pow(branch_end[1] - branch_start[1], 2) + pow(branch_end[2] - branch_start[2], 2))
    math.floor(branch_length)
    if branch_length < 0.5:
        return
    branch_length_int = int(branch_length)
    if branch_length_int < 1:
            branch_length_int = 1
            
    dir_x = (branch_end[0] - branch_start[0])/branch_length
    dir_y = (branch_end[1] - branch_start[1])/branch_length
    dir_z = (branch_end[2] - branch_start[2])/branch_length
    
    dir_x_end = dir_z
    dir_z_end = -dir_x

    for i in range(int(branch_length_int)):
        
        child_branch_start = branch_start.copy()
        child_branch_start[0] = child_branch_start[0] + dir_x * i #x pajuda 1 atgal
        child_branch_start[1] = child_branch_start[1] + dir_y * i
        child_branch_start[2] = child_branch_start[2] + dir_z * i #z pajuda 1 atgal
            
        child_branch_end = child_branch_start.copy()
        child_branch_end[0] = child_branch_start[0] + dir_x_end * (branch_length - i) * 0.3 + dir_x * 2
        child_branch_end[1] = child_branch_start[1] + dir_y * 2
        child_branch_end[2] = child_branch_start[2] + dir_z_end * (branch_length - i) * 0.3 + dir_z * 2
            
        add.cylinder(child_branch_start, child_branch_end, 0.1, 4, green)
            
        child_branch_end_other = child_branch_start.copy()
        child_branch_end_other[0] = child_branch_start[0] - dir_x_end * (branch_length - i) * 0.3 + dir_x * 2
        child_branch_end_other[1] = child_branch_start[1] + dir_y * 2
        child_branch_end_other[2] = child_branch_start[2] - dir_z_end * (branch_length - i) * 0.3 + dir_z * 2

        add.cylinder(child_branch_start, child_branch_end_other, 0.1, 4, green)

def trunk(start, slices):
    cylinder_radius = 1
    start_point = start.copy()
    end_point = start.copy()
    end_point[1] = start_point[1] + 1
    for i in range(slices):
        if i < slices - 2:
            add.cylinder(start_point, end_point, cylinder_radius, 4, brown)
        elif i == slices - 2:
            add.cylinder(start_point, end_point, cylinder_radius, 4, green)
        else:
            add.cone(start_point, end_point, cylinder_radius, 4, green)
        start_point[1] = i + 1
        end_point[1] = i + 2
        cylinder_radius = cylinder_radius * 0.95
        rotation = 18 if i % 2 == 0 else 0  # alternate rotation
        for j in range(10):
            branch_length = max((slices - i) * 0.4, 1.5)
            
            angle_rad = math.radians(j * 36 + rotation)
            bx = math.cos(angle_rad) * branch_length
            bz = math.sin(angle_rad) * branch_length
            b_start = [start[0], i, start[2]]
            b_end = [start[0] + bx, i -2, start[2] + bz]
            if branch_length > 1:
                branch(b_start, b_end)


    cone_start = start_point.copy()
    cone_end = cone_start.copy()
    cone_end[1] = cone_end[1] + 2

#spikes on branches, maybe small cones or idk cylinders again maybe


def main():
    trunk_start = [0,0,0]
    slices = 32
    trunk(trunk_start, slices)

    add.off("fir_tree.off")
    
main()
