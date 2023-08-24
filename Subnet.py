# Author: Shantanu Wable

def calculate_subnet_details(ip_address, subnet_prefix_length):
  
    # Convert IP address to binary string
    ip_parts = ip_address.split('.')
    binary_ip = ''.join(format(int(part), '08b') for part in ip_parts)

    # Calculate subnet mask
    subnet_mask = '1' * subnet_prefix_length + '0' * (32 - subnet_prefix_length)
    subnet_mask_parts = [subnet_mask[i:i+8] for i in range(0, 32, 8)]
    decimal_subnet_mask = '.'.join(str(int(part, 2)) for part in subnet_mask_parts)

    # Calculate number of possible connections
    possible_connections = 2 ** (32 - subnet_prefix_length) - 2

    # Calculate network address
    network_address_binary = binary_ip[:subnet_prefix_length] + '0' * (32 - subnet_prefix_length)
    network_address_parts = [network_address_binary[i:i+8] for i in range(0, 32, 8)]
    decimal_network_address = '.'.join(str(int(part, 2)) for part in network_address_parts)

    # Calculate broadcast address
    broadcast_address_binary = binary_ip[:subnet_prefix_length] + '1' * (32 - subnet_prefix_length)
    broadcast_address_parts = [broadcast_address_binary[i:i+8] for i in range(0, 32, 8)]
    decimal_broadcast_address = '.'.join(str(int(part, 2)) for part in broadcast_address_parts)

    return {
        "Subnet Mask": decimal_subnet_mask,
        "Number of Possible Connections": possible_connections,
        "First IP Address": decimal_network_address,
        "Last IP Address": decimal_broadcast_address
    }

# Example usage
ip_address = "192.168.1.34"
subnet_prefix_length = 28
subnet_details = calculate_subnet_details(ip_address, subnet_prefix_length)
for key, value in subnet_details.items():
    print(f"{key}: {value}")
