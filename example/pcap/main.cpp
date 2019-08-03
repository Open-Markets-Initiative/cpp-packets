#include <omi/packet/definitions.hpp>
#include <iostream>

// Parse Pcap.Eth2.Ipv4.Upd Packet

int main() {
    using namespace omi;

    try {
        auto frames = pcap::map(R"(..\..\pcap\example.pcap)");
        for (const auto frame : frames) { // Do we need iterator to check if we read off end?

            auto current = frame->payload();
            std::cout << *frame << std::endl;

            // Parse eth2 header
            const auto ethernet = ethernet::header::decode(current);
            std::cout << *ethernet << std::endl;
 
            auto ethtype = ethernet->info;
            while (ethtype.vlan()) {
                const auto vlan = vlan::tag::decode(current);
                std::cout << *vlan << std::endl;

                ethtype = vlan->type;
            }

            // Parse ipv4 header
            if (ethtype.ipv4()) {
                auto ipv4 = ipv4::header::parse(current);
                std::cout << *ipv4 << std::endl;

                // Todo: udp
            }
        }    
    } catch (std::exception &exception) {
        std::cerr << "Error: " << exception.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }
     
    system("pause");
}