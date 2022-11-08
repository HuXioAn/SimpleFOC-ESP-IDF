
file(GLOB SUORCES "*.cpp")

idf_component_register( SRCS  ${SOURCE}
                        
                        INCLUDE_DIRS 
                        "./"
                        "./common" "./common/base_classes" 
                        "./communication" 
                        "./current_sense" "./current_sense/hardware_specific"
                        "./drivers/" "./drivers/hardware_specific"
                        "./sensors/"
                        REQUIRES freertos 
                        )


