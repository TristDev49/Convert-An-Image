// Global variables
let selectedFile = null;
let selectedFormat = 'png';

// Event listener when document loads
document.addEventListener('DOMContentLoaded', () => {
  const fileInput = document.querySelector('input[type="file"][aria-label="Upload image"]');
  const uploadArea = fileInput?.parentElement;
  const convertBtn = document.querySelector('.convert-btn');

  // File input event
  if (fileInput) {
    fileInput.addEventListener('change', (e) => {
      selectedFile = e.target.files[0];
      if (selectedFile) updateUploadText(selectedFile.name);
    });

    // Drag & drop events
    ['dragover', 'dragleave', 'drop'].forEach(eventType => {
      uploadArea.addEventListener(eventType, (e) => {
        e.preventDefault();
        if (eventType === 'dragover') {
          uploadArea.classList.add('border-accent', 'bg-indigo-50');
        } else if (eventType === 'dragleave') {
          uploadArea.classList.remove('border-accent', 'bg-indigo-50');
        } else if (eventType === 'drop') {
          uploadArea.classList.remove('border-accent', 'bg-indigo-50');
          const files = e.dataTransfer.files;
          if (files.length > 0) {
            selectedFile = files[0];
            fileInput.files = files;
            updateUploadText(selectedFile.name);
          }
        }
      });
    });
  }

  // Format radio button event
  document.querySelectorAll('input[type="radio"][name="format"]').forEach(radio => {
    radio.addEventListener('change', (e) => {
      if (e.target.checked) selectedFormat = e.target.value;
    });
  });

  // Convert button event
  if (convertBtn) {
    convertBtn.addEventListener('click', convertImage);
  }
});

// Update upload area text
function updateUploadText(fileName) {
  const uploadText = document.querySelector('.relative.border-2.border-dashed p.font-semibold');
  if (uploadText) {
    uploadText.textContent = fileName;
    uploadText.classList.add('text-accent');
  }
}

// Image conversion function
function convertImage() {
  // File validation
  if (!selectedFile) {
    alert('⚠️ Please select an image file first!');
    return;
  }

  if (!selectedFormat) {
    alert('⚠️ Please select an output format first!');
    return;
  }

  // File type validation
  const validTypes = ['image/jpeg', 'image/jpg', 'image/png', 'image/gif', 'image/bmp', 'image/webp'];
  if (!validTypes.includes(selectedFile.type)) {
    alert('⚠️ The selected file is not a valid image!\n\nSupported formats: JPEG, JPG, PNG, GIF, BMP, WebP');
    return;
  }

  // Create output file name
  const inputFileName = selectedFile.name;
  const fileNameWithoutExt = inputFileName.substring(0, inputFileName.lastIndexOf('.')) || inputFileName;
  const outputFileName = `${fileNameWithoutExt}.${selectedFormat}`;

  // Read file
  const reader = new FileReader();
  
  reader.onload = function(e) {
    // Convert to base64
    const arrayBuffer = e.target.result;
    const bytes = new Uint8Array(arrayBuffer);
    let binary = '';
    for (let i = 0; i < bytes.byteLength; i++) {
      binary += String.fromCharCode(bytes[i]);
    }
    const base64 = btoa(binary);
    
    // Send to C++
    const message = base64 + "|" + outputFileName + "|" + selectedFormat;
    
    if (window.chrome && window.chrome.webview) {
      chrome.webview.postMessage(message);
      console.log("Sending to C++:", outputFileName);
    } else {
      alert('WebView2 is not available! Run from the C++ executable.');
    }
  };
  
  reader.onerror = () => alert('Error reading file: ' + reader.error);
  reader.readAsArrayBuffer(selectedFile);
}