#include <omi/packet/definitions.hpp>

// Example: Parse Pcap.Eth2.Ipv4.Upd.Sbe Packet

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
            if (not ethtype.ipv4()) { continue; }

            auto ipv4 = ipv4::header::decode(current);
            std::cout << *ipv4 << std::endl;

            auto ipv4type = ipv4->protocol;

            // Parse udp header
            if (not ipv4type.udp()) { continue; }

            auto udp = udp::header::parse(current);
            std::cout << *udp << std::endl;

            // Todo: cme

            std::cout << std::endl;
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