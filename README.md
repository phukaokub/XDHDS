Here's the revised version of your GitHub README based on the updated title and abstract:

---

# XDHDS: Cross-Domain Healthcare Data Sharing Using Self-Sovereign Identity and Adaptive Proxy Re-Encryption

XDHDS is a secure, decentralized model for managing and sharing healthcare data across multiple domains and regions. Built on blockchain technology, it integrates Self-Sovereign Identity (SSI) and Ciphertext-Policy Attribute-Based Encryption (CP-ABE) to provide robust, fine-grained access control. XDHDS enhances patient control over Electronic Health Records (EHRs) while ensuring secure, cross-regional data sharing. The system also supports distributed proxy re-encryption, allowing efficient handling of large datasets.

## Features

- Self-Sovereign Identity (SSI) for decentralized digital identity management.
- Ciphertext-Policy Attribute-Based Encryption (CP-ABE) for fine-grained access control.
- Adaptive Proxy Re-Encryption for secure cross-regional data access.
- Cross-domain authentication and authorization.
- Scalability to handle large healthcare datasets with efficient re-encryption.

## Getting Started

### Prerequisites

- Python 3.x
- Blockchain infrastructure (e.g., Ethereum or Hyperledger)
<!--- - Required Python libraries (install via `requirements.txt`) --->
- Cloud storage services (for EHR storage)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/XDHDS.git
   ```
2. Navigate to the project directory:
   ```bash
   cd XDHDS
   ```
<!---3. Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```--->

### Usage

1. **Data Owner**:
   - Navigate to the `Data_Owner` folder.
   - Run the `CP-ABE.py` file to perform the encryption and decryption process:
     ```bash
     python CP-ABE.py
     ```
   - This tests the complete encryption-decryption cycle.

2. **Access Requester**:
   - Navigate to the `Access_Requester` folder.
   - Run `Policy-Update.py` to test proxy re-encryption:
     ```bash
     python Policy-Update.py
     ```

3. **Distributed Proxy Test**:
   - To test parallel multi-proxy re-encryption, run `test-distributed.py`:
     ```bash
     python test-distributed.py
     ```

## Contributing

Contributions are welcome! Please fork this repository, make your changes, and submit a pull request. Ensure that your code adheres to the project's coding standards.

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.

## Acknowledgments

We would like to thank Sirindhorn International Institute of Technology, Thammasat University, for providing the resources and guidance for this project.

## Contact

For any inquiries or contributions:

1st Danupat Chainarong  
School of ICT, SIIT, Thammasat University  
Email: 6422770261@siit.tu.ac.th  

2nd Krittin Thirasak  
School of ICT, SIIT, Thammasat University  
Email: 6422780088@siit.tu.ac.th  

3rd Teerawat Chuaphanngam  
School of ICT, SIIT, Thammasat University  
Email: 6422780054@siit.tu.ac.th

---

This README should align with the new title, abstract, and folder structure provided. Let me know if you need any further adjustments!
