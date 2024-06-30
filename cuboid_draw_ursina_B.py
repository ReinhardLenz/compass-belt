from ursina import *
from serial import Serial, SerialException
# Set up serial connection
try:
    serialPort = Serial(port="COM6", baudrate=9600, timeout=0.5)
except SerialException:
    print("Could not open serial port. Please check the port name and your permissions.")
    exit()
# Initialize the Ursina engine
app = Ursina()
window.color = color.rgb(0, 0, 255)  # Set background to blue
# Create a red cuboid
cuboid = Entity(
    model='cube',
    color=color.red,
    scale=(4, .5, 2)
)

def setup_lighting():
    # Create a directional light
    directional_light = DirectionalLight()
    directional_light.look_at(Vec3(1, -1, -1))  # Direction the light is pointing towards
    directional_light.cast_shadow = True  # Enable casting shadows
    # Further configurations if you want to customize the light
    directional_light.shadow_map_size = 2048  # Higher values give better shadow resolution
    directional_light.falloff = 10  # Controls the light's attenuation
    directional_light.color = color.white

nw_text = None
def add_text_to_scene(text_string, x_position, y_position):
    global nw_text
    # If nw_text is None, this is the first time setting the text
    if nw_text is None:
        nw_text = Text(
            text=text_string,  # The text you want to display
            position=(x_position, y_position)  # The screen position for the text
        )
    else:
        # Update the text of the existing Text entity
        nw_text.text = text_string
def update():
    global nw_text
    """
    Update the cuboid's orientation based on gyrometer data.
    """
    if serialPort.inWaiting() > 0:
        data_bytes = serialPort.readline()
        try:
            # Decode using UTF-8 and replace errors
            data_str = data_bytes.decode('utf-8', errors='replace').strip()
            # Parse the gyrometer data assuming the format "X: value Y: value Z: value"
            data_parts = data_str.split()
            x = float(data_parts[1])   # gyro.x()
            y = float(data_parts[3])   # gyro.y()
            z = float(data_parts[5])   # gyro.z()
            a = data_parts[7]   # angle
            # Update cuboid's rotation (pitch, yaw, and roll)
            cuboid.rotation_x = -z % 360  # Convert angles to 0-360 range
            cuboid.rotation_y = x % 360
            cuboid.rotation_z = y % 360
            # Update the nw_text entity with new data (or create it if it doesn't exist)
            add_text_to_scene(a, x_position=-0.45, y_position=0.45)
        except (ValueError, IndexError) as e:
            print(f"Error parsing data: {e}")
            pass# Set the update function to be called every frame



def start():
    #app = Ursina()

    # Set up the scene with lighting
    setup_lighting()
    # Create a red cuboid

    ground = Entity(
        model='plane',
        scale=(10, 10, 10),
        color=color.gray,
        position=(0, -0.1, 0),
        receive_shadow=True
    )
   
    # Example to add ambient light to the scene
    AmbientLight(color=color.rgba(100, 100, 100, 100))
    EditorCamera()
    app.run()
if __name__ == '__main__':
    start()