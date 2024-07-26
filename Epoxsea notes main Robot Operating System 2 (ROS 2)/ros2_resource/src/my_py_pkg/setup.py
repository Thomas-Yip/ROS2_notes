from setuptools import setup

package_name = 'my_py_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ubuntu',
    maintainer_email='ubuntu@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "py_node = my_py_pkg.my_first_code:main",
            "radio = my_py_pkg.radio_station:main",
            "RTHK = my_py_pkg.ex_1:main",
            "smartphone = my_py_pkg.smartphone:main",
            "num_pub = my_py_pkg.pub_num:main",
            "num_count = my_py_pkg.num_counter:main",
            "addTwoIntsServer = my_py_pkg.add_two_ints_server:main",
            "addTwoIntsClientNoOop = my_py_pkg.add_two_ints_client_nooop:main",
            "num_count_server = my_py_pkg.num_counter:main",
            "reset_counter_client = my_py_pkg.reset_counter_client:main",
            "hw_status_publisher = my_py_pkg.hw_status_publisher:main",
            "add_two_ints_client_oop = my_py_pkg.add_two_ints_client_oop:main",
            "battery = my_py_pkg.battery:main",
            "led_panel = my_py_pkg.led:main"
        ],
    },
)
